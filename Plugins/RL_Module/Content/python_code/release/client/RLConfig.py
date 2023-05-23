from rl.policy import BoltzmannQPolicy, EpsGreedyQPolicy, SoftmaxPolicy, GreedyQPolicy, MaxBoltzmannQPolicy
from tensorflow.keras.metrics import MeanSquaredError, MeanAbsoluteError, RootMeanSquaredError, \
    MeanSquaredLogarithmicError, LogCoshError

from tensorflow.keras.optimizers.legacy import Adam, RMSprop, SGD


class RLConfig:
    ue_policy = {'BoltzmannQPolicy': BoltzmannQPolicy(),
                 'EpsGreedyQPolicy': EpsGreedyQPolicy(),
                 'SoftmaxPolicy': SoftmaxPolicy(),
                 'GreedyQPolicy': GreedyQPolicy(),
                 'MaxBoltzmannQPolicy': MaxBoltzmannQPolicy()}

    ue_metrics = {"MAE": MeanAbsoluteError(),
                  "MSE": MeanSquaredError(),
                  "RMSE": RootMeanSquaredError(),
                  "MSLE": MeanSquaredLogarithmicError(),
                  "LCE": LogCoshError()}

    ue_optimizers = {"Adam": Adam,
                     "RMSprop": RMSprop,
                     "SGD": SGD}
