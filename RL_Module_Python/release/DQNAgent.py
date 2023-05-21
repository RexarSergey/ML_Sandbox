from rl.agents import DQNAgent
from rl.policy import BoltzmannQPolicy
from rl.memory import SequentialMemory

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten
from tensorflow.keras.optimizers.legacy import Adam

from release.client.command.CommandGetNetwork import CommandGetNetwork

class UnrealDQNAgent:

    def __init__(self, env):
        print(env.client.get_network())
        self.env = env
        self.states = env.observation_space.shape
        self.actions = env.action_space.n
        self.model = None

    def build_model(self):
        self.model = Sequential()
        self.model.add(Dense(16, activation='sigmoid', input_shape=self.states))
        self.model.add(Dense(8, activation='relu'))
        self.model.add(Dense(self.actions, activation='linear'))
        return self.model

    def build_agent(self):
        policy = BoltzmannQPolicy()
        memory = SequentialMemory(limit=50000, window_length=1)
        dqn = DQNAgent(model=self.model, memory=memory, policy=policy,
                       nb_actions=self.actions, nb_steps_warmup=10, target_model_update=1e-2)
        self.model = dqn
        return dqn

    def fit(self):
        self.model.compile(Adam(learning_rate=1e-2), metrics=['mae'])
        self.model.fit(self.env, nb_steps=1000, visualize=False, verbose=1)
