import torch

from torch import nn


class GeneralNNUE (nn.Module):
    """
    Configurable NNUE model.

    The network consists of a feature transformation layer, one hidden layer,
    and a single output neuron. All layers but the last one use ClippedReLU as
    activation function.

    :ivar nn.Linear feature_transformer: Input feature transformation layer.
    :ivar nn.Linear hidden: Hidden fully connected layer.
    :ivar nn.Linear output: Output layer producing a single evaluation value.
    """

    def __init__ (self, input_features, l1_size, l2_size):
        """
        Initialize the neural network.

        :param int input_features: Number of input features.
        :param int l1_size: Number of neurons in the feature transformation layer.
        :param int l2_size: Number of neurons in the hidden layer.
        """

        super().__init__()
        self.feature_transformer = nn.Linear(input_features, l1_size)
        self.hidden = nn.Linear(l1_size, l2_size)
        self.output = nn.Linear(l2_size, 1)

    def forward (self, x):
        """
        Perform a forward pass through the network.

        :param torch.Tensor x: Input tensor.

        :return torch.Tensor: Predicted evaluation for each input sample.
        """

        x = torch.clamp(self.feature_transformer(x), 0, 127)
        x = torch.clamp(self.hidden(x), 0, 127)
        return self.output(x)


class Omega5NNUE (nn.Module):
    """
    Fixed-architecture NNUE model used by Omega Five.

    The network consists of a 200-neuron feature transformation layer, one 
    64-neuron hidden layer, and a single neuron output layer.
    All layers but the last one use ClippedReLU as activation function.

    :ivar int INPUT_FEATURES: Number of input features.
    :ivar int L1_SIZE: Number of neurons in the feature transformer.
    :ivar int L2_SIZE: Number of neurons in the hidden layer.
    :ivar int CLAMP_MAX: Threshold for the ClippedReLU.
    :ivar nn.Linear feature_transformer: Input feature transformation layer.
    :ivar nn.Linear hidden: Hidden fully connected layer.
    :ivar nn.Linear output: Output layer producing a single evaluation value.
    """

    INPUT_FEATURES = 200
    L1_SIZE = 1024
    L2_SIZE = 64
    CLAMP_MAX = 127

    def __init__(self):
        """
        Initialize the neural network.
        """

        super().__init__()
        self.feature_transformer = nn.Linear(self.INPUT_FEATURES, self.L1_SIZE)
        self.hidden = nn.Linear(self.L1_SIZE, self.L2_SIZE)
        self.output = nn.Linear(self.L2_SIZE, 1)

    def forward (self, x):
        """
        Perform a forward pass through the network.

        :param torch.Tensor x: Input tensor.

        :return torch.Tensor: Predicted evaluation for each input sample.
        """
        
        x = torch.clamp(self.feature_transformer(x), 0, self.CLAMP_MAX)
        x = torch.clamp(self.hidden(x), 0, self.CLAMP_MAX)
        return self.output(x)
