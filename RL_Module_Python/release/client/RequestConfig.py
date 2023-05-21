class RequestConfig:
    ue_commands = {"step": 0,
                   "reset": 1,
                   "state": 2,
                   "reward": 3,
                   "is_done": 4,

                   "get_network": 5}

    def get_tasks(self):
        return self.ue_commands
