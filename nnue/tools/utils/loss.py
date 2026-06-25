import torch

from torch import nn


class Loss (nn.Module):
    def __init__ (self, k, w):
        super().__init__()
        self.k = k
        self.w = w
        self.mse = nn.MSELoss()

    def forward (self, y_pred, Y_true):
        y_eval = Y_true[:, 0]
        y_outcome = Y_true[:, 1]

        prediction = torch.sigmoid(self.k * y_pred.squeeze())
        target = self.w * torch.sigmoid(self.k * y_eval) + (1 - self.w) * y_outcome
        loss = self.mse(prediction, target)

        return loss
