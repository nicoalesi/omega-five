import numpy as np
import torch


class Dataset ():
    def __init__ (self):
        self.filepath = None
        self.chunk_size = None

    def set (self, filepath, chunk_size):
        self.filepath = filepath
        self.chunk_size = chunk_size

    def get (self):
        if self.filepath is None or self.chunk_size is None:
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
                    chunk = file.read(self.chunk_size)
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
        game_id = int.from_bytes(chunk[0:2], "little", signed = True)
        pos = self._bits_to_vec(chunk[2:27])
        score = int.from_bytes(chunk[27:29], "little", signed = True)
        outcome = int.from_bytes(chunk[29:30], "little", signed = False) / 2

        return game_id, pos, score, outcome
    
    def _bits_to_vec (self, chunk):
        return np.unpackbits(np.frombuffer(chunk, dtype = np.uint8))
