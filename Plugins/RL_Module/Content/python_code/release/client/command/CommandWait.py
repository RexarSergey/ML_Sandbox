from release.client.command.CommandBase import CommandBase


class CommandWait(CommandBase):

    def __init__(self, s):
        super().__init__()
        self.s_read = s

    def perform_action(self, **action_data):
        received = 0
        while received != "1":
            received = self.s_read.recv(32)
            received = received.decode("utf-8")
