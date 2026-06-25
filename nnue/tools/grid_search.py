import numpy as np
import torch
import torch.nn as nn
import sys

from utils.cross_validation import GroupKFold
from utils.dataset import Dataset
from utils.loss import Loss
from utils.model import GeneralNNUE

from torch.optim import AdamW
from torch.utils.data import TensorDataset, DataLoader


K = 0.00063
SEED = 42


def save_summary (loss_summary):
    with open("gkf_cv_loss_summary.txt", "w") as f:
        for config_idx, config_losses in enumerate(loss_summary):
            f.write(f"Configuration {config_idx + 1}\n\n")

            for fold_idx, fold_losses in enumerate(config_losses):
                f.write(f"Fold {fold_idx + 1}\n")

                for epoch_idx, (train_loss, val_loss) in enumerate(fold_losses):
                    f.write(
                        "    "
                        f"Epoch {epoch_idx + 1}: "
                        f"train_loss = {train_loss:.6f}, "
                        f"val_loss = {val_loss:.6f}\n"
                    )

                f.write("\n")
            
            f.write("\n\n")
    

def main ():
    configs = [
        {"input_features": 200, "l1_size": 256, "l2_size": 64, "lr": 0.00005},
        {"input_features": 200, "l1_size": 512, "l2_size": 32, "lr": 0.00005},
        {"input_features": 200, "l1_size": 512, "l2_size": 64, "lr": 0.00005},
        {"input_features": 200, "l1_size": 1024, "l2_size": 32, "lr": 0.000025},
        {"input_features": 200, "l1_size": 1024, "l2_size": 64, "lr": 0.000025},
    ]

    gkf = GroupKFold()
    dataset = Dataset()
    dataset.set("training.bin", 30)
    Xs, Ys = dataset.get()

    loss_summary = []

    for config in configs:
        config_losses = []

        for fold, data,  in enumerate(gkf.split(Xs, Ys)):
            fold_losses = []

            torch.manual_seed(SEED + fold)

            X_train, Y_train, X_val, Y_val = data

            train_dataset = TensorDataset(X_train, Y_train)
            train_loader = DataLoader(train_dataset, batch_size = 2048, shuffle = True)

            model = GeneralNNUE(
                input_features = config["input_features"],
                l1_size = config["l1_size"],
                l2_size = config["l2_size"]
            )

            criterion = Loss(k = K, w = 0.7)
            adjusted_lr = config["lr"] / K
            adjusted_decay = 0.01 * K
            optimizer = AdamW(model.parameters(), lr = adjusted_lr, weight_decay = adjusted_decay)

            epochs = 3
            for epoch in range(epochs):
                model.train()
                train_loss = 0.0

                for batch_X, batch_Y in train_loader:
                    optimizer.zero_grad()

                    predictions = model(batch_X)
                    loss = criterion(predictions, batch_Y)

                    loss.backward()
                    optimizer.step()

                    train_loss += loss.item()

                model.eval()
                val_loss = 0.0

                with torch.no_grad():
                    val_predictions = model(X_val)
                    val_loss = criterion(val_predictions, Y_val).item()
                
                fold_losses.append((train_loss / len(train_loader), val_loss))
            
            config_losses.append(fold_losses)

        loss_summary.append(config_losses)               

    save_summary(loss_summary)


if __name__ == "__main__":
    main()
