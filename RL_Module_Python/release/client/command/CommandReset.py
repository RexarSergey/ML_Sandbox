from release.client.command.CommandBase import CommandBase
from release.client.RequestConfig import RequestConfig
from release.client.command.CommandState import CommandState
from release.client.command.CommandWait import CommandWait
import json


class CommandReset(CommandBase):

    def __init__(self, s_write, s_read):
        super().__init__()
        self.s_write = s_write
        self.s_read = s_read
        self.config = RequestConfig.ue_commands

    def perform_action(self, **action_data):
        try:
            data = self.get_data(**action_data)
            self.s_write.sendall(bytes(json.dumps(data), encoding="utf-8"))
            print("post: reset")

            wait = CommandWait(self.s_read)
            wait.perform_action()
            state = CommandState(self.s_write, self.s_read)
            return state.perform_action()

        except:
            print("reset: connection failed or interrupted")

    def get_data(self, **data):
        return {'id': self.config['reset'], 'action': [0]}
