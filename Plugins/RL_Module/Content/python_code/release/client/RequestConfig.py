class RequestConfig:
    ue_commands = {"step": 0,
                   "reset": 1,
                   "state": 2,
                   "reward": 3,
                   "is_done": 4,

                   "get_dqn_struct": 5,
                   "get_gym_struct": 6}

    def get_tasks(self):
        return self.ue_commands
