import socket
import json

from release.client.command.CommandState import CommandState
from release.client.command.CommandReward import CommandReward
from release.client.command.CommandReset import CommandReset
from release.client.command.CommandIsDone import CommandIsDone
from release.client.command.CommandStep import CommandStep
from release.client.command.CommandWait import CommandWait
from release.client.command.CommandGetNetwork import CommandGetNetwork


class ClientCommunication:
    s_write = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_read = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def __init__(self, host, port):

        self.host = host
        self.port = port

        try:
            self.s_write.connect((self.host, self.port))
            print("connected! (main)")
        except:
            print("connection failed or interrupted (main)")

        try:
            self.s_read.connect((self.host, self.port - 1))
            print("connected! (notify)")
        except:
            print("connection failed or interrupted (notify)")

    def step(self, action):
        comm = CommandStep(self.s_write, self.s_read)
        return comm.perform_action(action=action)

    def reset(self):
        comm = CommandReset(self.s_write, self.s_read)
        return comm.perform_action()

    def state(self):
        comm = CommandState(self.s_write, self.s_read)
        return comm.perform_action()

    def reward(self):
        comm = CommandReward(self.s_write, self.s_read)
        return comm.perform_action()

    def is_done(self):
        comm = CommandIsDone(self.s_write, self.s_read)
        return comm.perform_action()

    def get_network(self):
        comm = CommandGetNetwork(self.s_write, self.s_read)
        return comm.perform_action()

    def wait(self):
        comm = CommandWait(self.s_read)
        comm.perform_action()