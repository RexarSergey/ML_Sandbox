from release.client.command.CommandBase import CommandBase
from release.client.RequestConfig import RequestConfig
from release.client.command.CommandWait import CommandWait
from release.client.command.CommandState import CommandState
from release.client.command.CommandReward import CommandReward
from release.client.command.CommandIsDone import CommandIsDone
import json


class CommandStep(CommandBase):

    def __init__(self, s_write, s_read):
        super().__init__()
        self.s_write = s_write
        self.s_read = s_read
        self.config = RequestConfig.ue_commands

    def perform_action(self, **action_data):
        # try:
        data = self.get_data(**action_data)
        print(data)
        self.s_write.sendall(bytes(json.dumps(data), encoding="utf-8"))
        print("post: step")

        wait = CommandWait(self.s_read)
        wait.perform_action()

        info_ = {}
        observation_ = CommandState(self.s_write, self.s_read).perform_action()
        reward_ = CommandReward(self.s_write, self.s_read).perform_action()
        done_ = CommandIsDone(self.s_write, self.s_read).perform_action()
        return observation_, reward_, done_, info_

    # except:
    #     print("step: connection failed or interrupted")

    def get_data(self, **action_data):
        action = action_data['action']
        data = {'id': self.config['step'], 'action': []}
        if not hasattr(action, '__iter__'):
            data['action'] = [float(action)]
        else:
            try:
                data['action'] = list(action.tolist())
            except:
                try:
                    data['action'] = list(action)
                except:
                    data['action'] = [action]
            for i in range(len(data['action'])):
                data['action'][i] = float(data['action'][i])
        return data
