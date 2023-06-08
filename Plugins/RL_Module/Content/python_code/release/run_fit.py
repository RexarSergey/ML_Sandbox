import sys
import os
import time

sys.path.append(os.getcwd())
print("Current working directory: {0}".format(os.getcwd()))

from release.rl.env.UnrealEnv import UnrealEnv
from release.rl.agent.DQNAgent import UnrealDQNAgent

print("params:")
for el in sys.argv:
    print(el)


def run_fit():
    try:
        env = UnrealEnv(sys.argv[1], int(sys.argv[2]))
        if env.ready:
            model = UnrealDQNAgent(env)
            model.build_from_unreal()
            model.fit()
            model.save_agent(sys.argv[3])
        return env.ready
    except Exception as e:
        print("Error: ", str(e))
        return False


try_run = True
while try_run:
    print("Try fit...")
    try_run = not run_fit()
    time.sleep(1)
time.sleep(100)
