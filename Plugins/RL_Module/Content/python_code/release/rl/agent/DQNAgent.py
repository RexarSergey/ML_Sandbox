import json

import gym
import numpy as np
from rl.agents import DQNAgent
from rl.memory import SequentialMemory
from tensorflow.keras.layers import Dense
from tensorflow.keras.models import Sequential

from release.client.RLConfig import RLConfig


class UnrealDQNAgent:

    def __init__(self, env):
        self.env = env
        self.model = None
        self.dqn = None
        self.policy = None
        self.dqn_struct = None
        self.states = None
        self.actions = None
        # self.dqn_struct = env.client.get_dqn_struct()
        # print("dqn data: ", self.dqn_struct)
        #
        # self.env = env
        # self.env.action_space = gym.spaces.Discrete(self.dqn_struct['actionLength'])
        # self.env.observation_space = gym.spaces.Box(low=np.array(self.dqn_struct['low']),
        #                                             high=np.array(self.dqn_struct['high']))
        #
        # self.states = env.observation_space.shape
        # self.actions = env.action_space.n
        #
        # self.model = None
        # self.dqn = None
        # self.policy = None

    def build_from_file(self, path):
        self.load_struct(path)
        print("dqn data: ", self.dqn_struct)
        self.build()
        self.load_agent(path)
        print("Loaded!")

    def build_from_unreal(self):
        self.dqn_struct = self.env.client.get_dqn_struct()
        print("dqn data: ", self.dqn_struct)
        self.build()

    def build(self):
        self.env.action_space = gym.spaces.Discrete(self.dqn_struct['actionLength'])
        self.env.observation_space = gym.spaces.Box(low=np.array(self.dqn_struct['low']),
                                                    high=np.array(self.dqn_struct['high']))

        self.states = self.env.observation_space.shape
        self.actions = self.env.action_space.n

        self.build_model()
        self.build_agent()

    def build_model(self):
        self.model = Sequential()

        self.model.add((Dense(self.dqn_struct['network'][0],
                              activation=self.dqn_struct['activations'][0],
                              input_shape=self.states)))
        for i in range(1, len(self.dqn_struct['network'])):
            neurones_count = self.dqn_struct['network'][i]
            activation = self.dqn_struct['activations'][i]
            self.model.add(Dense(neurones_count, activation=activation))
        self.model.add(Dense(self.actions, activation='linear'))
        return self.model

    def build_agent(self):
        self.policy = RLConfig.ue_policy[self.dqn_struct['policy']]  # customise
        memory = SequentialMemory(limit=50000, window_length=1)
        self.dqn = DQNAgent(model=self.model,
                            memory=memory,
                            policy=self.policy,
                            nb_actions=self.actions,
                            nb_steps_warmup=self.dqn_struct['stepsWarmup'],
                            target_model_update=self.dqn_struct['targetModelUpdate'])  # customise
        metrics = self.make_metrics()
        optimizer = RLConfig.ue_optimizers[self.dqn_struct['optimizer']]
        self.dqn.compile(optimizer(learning_rate=self.dqn_struct['learningRate']),  # customise
                         metrics=metrics)  # customise
        return self.dqn

    def fit(self):
        self.dqn.fit(self.env,
                     nb_steps=self.dqn_struct['steps'],
                     visualize=False,
                     verbose=1)  # customise

    def make_metrics(self):
        copy = []
        for i in range(len(self.dqn_struct['metrics'])):
            x = self.dqn_struct['metrics'][i]
            #self.dqn_struct['metrics'][i] = RLConfig.ue_metrics[x]
            copy.append(RLConfig.ue_metrics[x])
        return copy

    def save_agent(self, path):
        try:
            with open(path + ".json", "w") as fp:
                json.dump(self.dqn_struct, fp)
            self.dqn.save_weights(path + ".h5", overwrite=True)
            print("Saved!")
        except:
            print("save agent: cannot save the model")

    def load_struct(self, path):
        try:
            with open(path + ".json") as fp:
                self.dqn_struct = json.load(fp)
        except:
            print("load struct: cannot load the model")

    def load_agent(self, path):
        try:
            self.dqn.load_weights(path + ".h5")
        except:
            print("load agent: cannot load the model")
