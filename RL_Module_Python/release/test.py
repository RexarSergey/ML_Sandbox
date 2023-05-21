

class A:
    def get(self):
        return self
    pass

d = {A: 1}
a = A
print(d[A])