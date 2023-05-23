class CommandBase:
    name = ""
    log_action = False

    def __init__(self):
        pass

    def perform_action(self, **action_data):
        raise NotImplementedError()
