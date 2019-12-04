from matplotlib import pyplot as plt
from scipy import signal
import os

here = os.path.dirname(os.path.abspath(__file__))  # find the working dir path
test_file = os.path.join(here, 'data.txt')        # create correct dir path


data = open(test_file)
y = data.read()
y = y.split()
for i in range(0, len(y)):
    y[i] = int(y[i])
print(y)
x = len(y)
print(x)
plt.plot(y)
plt.show()
