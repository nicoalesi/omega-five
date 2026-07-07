import numpy as np
import torch


class Dataset ():
    """
    Dataset loader for binary-encoded game data.

    Reads a binary dataset in which each record represents a game position,
    groups positions by game ID, and returns the data as lists of
    PyTorch tensors (one tensor per game).

    :ivar str filepath: Path to the binary dataset file.
    """

    def __init__ (self):
        """
        Initialize an empty dataset loader.
        """

        self.filepath = None

    def set (self, filepath):
        """
        Configure the dataset source.

        :param str filepath: Path to the binary dataset file.
        """

        self.filepath = filepath

    def get (self):
        """
        Load the dataset from the configured file.

        :return tuple[list[torch.Tensor], list[torch.Tensor]] | None:
            A tuple ``(positions, labels)``, where each list contains one
            tensor per game. Returns ``None`` if the dataset has not been
            configured.
        """

        if self.filepath is None:
            return None
        
        tot_positions = []
        tot_labels = []

        with open(self.filepath, "rb") as file:
            data_left = True
            curr_game_id = 0

            game_positions = []
            game_labels = []

            while data_left:
                next_positions = []
                next_labels = []

                while True:
                    chunk = file.read(30)
                    if not chunk:
                        data_left = False
                        break

                    game_id, pos, score, outcome = self._unpack_chunk(chunk)

                    if game_id != curr_game_id:
                        curr_game_id = game_id
                        next_positions.append(pos)
                        next_labels.append(np.array([score, outcome], dtype = np.float32))
                        break

                    game_positions.append(pos)
                    game_labels.append(np.array([score, outcome], dtype = np.float32))
                
                tot_positions.append(torch.from_numpy(np.stack(game_positions, dtype = np.float32)))
                tot_labels.append(torch.from_numpy(np.stack(game_labels, dtype = np.float32)))

                game_positions = next_positions.copy()
                game_labels = next_labels.copy()

        return tot_positions, tot_labels

    def _unpack_chunk (self, chunk):
        """
        Decode a single binary record.

        :param bytes chunk: Binary record of size 30.

        :return tuple[int, numpy.ndarray, int, float]:
            A tuple ``(game_id, position, score, outcome)`` containing the
            decoded game ID, bit-vector representation of the board,
            evaluation score, and game outcome.
        """

        game_id = int.from_bytes(chunk[0:2], "little", signed = True)
        pos = self._bits_to_vec(chunk[2:27])
        score = int.from_bytes(chunk[27:29], "little", signed = True)
        outcome = int.from_bytes(chunk[29:30], "little", signed = False) / 2

        return game_id, pos, score, outcome
    
    def _bits_to_vec (self, chunk):
        """
        Convert packed board bits into a binary vector.

        :param bytes chunk: Packed binary representation of a board position.

        :return numpy.ndarray: A one-dimensional array containing the unpacked bits.
        """

        return np.unpackbits(np.frombuffer(chunk, dtype = np.uint8))
