import torch

from torch import nn


class Loss (nn.Module):
    """
    Custom loss function.

    :ivar float k: Scaling factor applied before the sigmoid transformation.
    :ivar float w: Weight assigned to the evaluation score when computing the target.
    :ivar nn.MSELoss mse: Mean squared error loss module.
    """

    def __init__ (self, k, w):
        """
        Initialize the class.

        :param float k: Scaling factor applied before the sigmoid transformation.
        :param float w: Weight assigned to the evaluation score in the target.
        """

        super().__init__()
        self.k = k
        self.w = w
        self.mse = nn.MSELoss()

    def forward (self, y_pred, Y_true):
        """
        Compute the loss for a batch of predictions.

        ``Y_true`` is expected to contain two columns:
        - column 0: evaluation score;
        - column 1: game outcome.

        :param torch.Tensor y_pred: Predicted evaluation scores.
        :param torch.Tensor Y_true: Ground-truth tensor containing evaluation
            scores and game outcomes.

        :return torch.Tensor:
            Mean squared error loss between the transformed predictions
            and the weighted target values.
        """

        y_eval = Y_true[:, 0]
        y_outcome = Y_true[:, 1]

        prediction = torch.sigmoid(self.k * y_pred.squeeze())
        target = self.w * torch.sigmoid(self.k * y_eval) + (1 - self.w) * y_outcome
        loss = self.mse(prediction, target)

        return loss
