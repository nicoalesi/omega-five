import sys
import torch


class GroupKFold ():
    def __init__ (self, n_splits = 5):
        self.n_splits = n_splits
    
    def split (self, Xs, Ys):
        counts = [X.shape[0] for X in Xs]

        if self.n_splits > len(Xs):
            print("Error: The number of unique groups must be greater than the number of splits.")
            sys.exit(1)

        X_folds = [[] for _ in range(self.n_splits)]
        Y_folds = [[] for _ in range(self.n_splits)]
        fold_counts = [0] * self.n_splits

        sorted_group_idxs = sorted(range(len(counts)), key = lambda i: counts[i], reverse = True)

        for group_idx in sorted_group_idxs:
            count = counts[group_idx]
            best_fold_idx = fold_counts.index(min(fold_counts))

            X_folds[best_fold_idx].append(Xs[group_idx])
            Y_folds[best_fold_idx].append(Ys[group_idx])
            fold_counts[best_fold_idx] += count

        for fold_idx in range(self.n_splits):
            train_Xs, train_Ys = [], []
            test_Xs, test_Ys = [], []

            for idx in range(self.n_splits):
                if idx == fold_idx:
                    test_Xs.extend(X_folds[idx])
                    test_Ys.extend(Y_folds[idx])
                else:
                    train_Xs.extend(X_folds[idx])
                    train_Ys.extend(Y_folds[idx])
            
            X_train = torch.cat(train_Xs, dim = 0)
            Y_train = torch.cat(train_Ys, dim = 0)
            X_test = torch.cat(test_Xs, dim = 0)
            Y_test = torch.cat(test_Ys, dim = 0)
            
            yield X_train, Y_train, X_test, Y_test
