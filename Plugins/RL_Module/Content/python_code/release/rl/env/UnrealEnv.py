from release.client.ClientCommunication import ClientCommunication
import gym
from gym.spaces import Discrete, Box
import numpy as np


class UnrealEnv(gym.Env):

    def __init__(self, host, port):
        # self.action_space = Discrete(5)
        # self.observation_space = Box(low=np.array([0]), high=np.array([100]))
        self.client = ClientCommunication(host, port)
        self.ready = self.client.success


    def step(self, act):
        return self.client.step(act)

    def render(self):
        return None

    def reward(self):
        return self.client.reward()

    def state(self):
        return self.client.state()

    def done(self):
        return self.client.is_done()

    def reset(self):
        return self.client.reset()


