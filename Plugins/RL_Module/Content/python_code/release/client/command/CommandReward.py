from release.client.command.CommandBase import CommandBase
from release.client.RequestConfig import RequestConfig
import json


class CommandReward(CommandBase):

    def __init__(self, s_write, s_read):
        super().__init__()
        self.s_write = s_write
        self.s_read = s_read
        self.config = RequestConfig.ue_commands

    def perform_action(self, **action_data):
        try:
            data = self.get_data(**action_data)
            self.s_write.sendall(bytes(json.dumps(data), encoding="utf-8"))

            received = self.s_read.recv(2048)
            received = received.decode('utf-8')
            received = json.loads(received)

            if self.log_action:
                print("get: reward")
            return received['reward']

        except:
            print("reward: connection failed or interrupted")

    def get_data(self, **data):
        return {'id': self.config['reward'], 'action': [0]}
