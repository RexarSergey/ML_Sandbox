import sys
import os
import time

sys.path.append(os.getcwd())
print("Current working directory: {0}".format(os.getcwd()))

print("params:")
for el in sys.argv:
    print(el)

from release.rl.env.UnrealEnv import UnrealEnv
from release.rl.agent.DQNAgent import UnrealDQNAgent


def run_ai():
    try:
        env = UnrealEnv(sys.argv[1], int(sys.argv[2]))
        if env.ready:
            env.reset()
            model = UnrealDQNAgent(env)
            model.build_from_file(sys.argv[4])
            while not env.done():
                env.step(model.dqn.forward(model.env.state()))
            print('Got Done')

        return env.ready
    except:
        return False


try_run = True
while try_run:
    print("Try fit...")
    try_run = not run_ai()
    time.sleep(1)
time.sleep(100)
