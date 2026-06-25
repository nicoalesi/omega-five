import torch

from torch import nn


class GeneralNNUE (nn.Module):
    def __init__ (self, input_features, l1_size, l2_size):
        super().__init__()
        self.feature_transformer = nn.Linear(input_features, l1_size)
        self.hidden = nn.Linear(l1_size, l2_size)
        self.output = nn.Linear(l2_size, 1)

    def forward (self, x):
        x = torch.clamp(self.feature_transformer(x), 0, 127)
        x = torch.clamp(self.hidden(x), 0, 127)
        return self.output(x)
