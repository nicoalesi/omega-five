import numpy as np
import torch

from utils.dataset import Dataset
from utils.loss import Loss
from utils.model import Omega5NNUE

from torch.optim import AdamW
from torch.utils.data import TensorDataset, DataLoader, random_split


K = 0.00063
W = 0.9
LR = 5e-6
WD = 0.1

BATCH_SIZE = 4096
TRAINING_FILES = 8
SEED = 42
EPOCHS = 1

FT_SCALE = float(1 << 20)
HL_SCALE = float(1 << 7)
OUT_SCALE = float(1 << 7)

INT8_MIN, INT8_MAX = -128, 127
INT32_MIN, INT32_MAX = -2147483648, 2147483647


def set_seed (seed):
    """
    Set the random seed for NumPy and PyTorch.

    :param int seed: Seed value used to initialize the random number generators.
    """

    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)


def export_quantized_weights (model, file = "weights.nnue"):
    """
    Scale, quantize, and export the model weights to a packed binary file.

    The network parameters are scaled, rounded, clipped to the target integer
    ranges, and written in binary format. The feature transformation weight
    matrix is transposed before being stored to improve cache locality during
    inference.

    :param nn.Module model: Trained model to export.
    :param str file: Path of the output binary weight file.
    """

    model.eval()

    ft_w = model.feature_transformer.weight.detach().cpu().numpy()
    ft_b = model.feature_transformer.bias.detach().cpu().numpy()

    hl_w = model.hidden.weight.detach().cpu().numpy()
    hl_b = model.hidden.bias.detach().cpu().numpy()

    out_w = model.output.weight.detach().cpu().numpy()
    out_b = model.output.bias.detach().cpu().numpy()

    ft_w = np.clip(np.round(ft_w * FT_SCALE), INT32_MIN, INT32_MAX).astype(np.int32)
    ft_b = np.clip(np.round(ft_b * FT_SCALE), INT32_MIN, INT32_MAX).astype(np.int32)

    hl_w = np.clip(np.round(hl_w * HL_SCALE), INT8_MIN, INT8_MAX).astype(np.int8)
    hl_b = np.clip(np.round(hl_b * HL_SCALE), INT32_MIN, INT32_MAX).astype(np.int32)

    out_w = np.clip(np.round(out_w * OUT_SCALE), INT8_MIN, INT8_MAX).astype(np.int8)
    out_b = np.clip(np.round(out_b * OUT_SCALE), INT32_MIN, INT32_MAX).astype(np.int32)
    
    # First weight matrix transposed to improve cache locality
    with open(file, "wb") as f:
        f.write(ft_w.T.tobytes())
        f.write(ft_b.tobytes())
        f.write(hl_w.tobytes())
        f.write(hl_b.tobytes())
        f.write(out_w.tobytes())
        f.write(out_b.tobytes())


def main ():
    """
    Train the Omega5 NNUE model and export its quantized weights.
    """

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print("Using device:", device)

    set_seed(SEED)

    totXs = []
    totYs = []

    dataset = Dataset()

    for i in range(TRAINING_FILES):
        dataset.set(f"training{i}.bin")
        Xs, Ys = dataset.get()

        totXs.extend(Xs)
        totYs.extend(Ys)

    model = Omega5NNUE().to(device)
    X = torch.cat(totXs)
    Y = torch.cat(totYs)

    permutation = torch.randperm(X.size(0))

    X = X[permutation]
    Y = Y[permutation]

    train_dataset = TensorDataset(X, Y)
    train_loader = DataLoader(train_dataset, batch_size = BATCH_SIZE, shuffle = True)

    criterion = Loss(k = K, w = W)
    optimizer = AdamW(model.parameters(), lr = LR, weight_decay = WD)

    model.train()
    for epoch in range(EPOCHS):
        for batch_X, batch_Y in train_loader:
            batch_X = batch_X.to(device)
            batch_Y = batch_Y.to(device)

            optimizer.zero_grad()

            predictions = model(batch_X)
            loss = criterion(predictions, batch_Y)

            loss.backward()
            optimizer.step()

    # Weights overview
    for name, param in model.named_parameters():
        weights = param.detach() 
        
        print(f"Layer: {name}")
        print(f"   Min:  {weights.min().item():.6f}")
        print(f"   Max:  {weights.max().item():.6f}")
        print(f"   Mean: {weights.mean().item():.6f}")

    export_quantized_weights(model)


if __name__ == "__main__":
    main()
