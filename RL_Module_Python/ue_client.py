import socket
from time import sleep


class UEClient:

    def __init__(self, host, port):
        self.host = host
        self.port = port

    def run(self):
        while True:
            try:
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                    s.connect((self.host, self.port))
                    print("connected!")
                    sleep(20)
                    # s.sendall(b"Hello, world")
                    # data = s.recv(1024)
            except:
                print("connection failed or interrupted")
                sleep(1)

    @property
    def rl_implementation(self):
        """The RLImplementation property."""
        return self.rl_implementation

    @rl_implementation.setter
    def rl_implementation(self, value):
        print("Set radius")
        self.rl_implementation = value
