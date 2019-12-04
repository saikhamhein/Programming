from matplotlib import pyplot as plt
from scipy import signal
data = open("data.txt")
y = data.read()
y = y.split()
for i in range(0, len(y)):
    y[i] = int(y[i])
print(y)
x = len(y)
print(x)
plt.plot(y)
plt.show()
