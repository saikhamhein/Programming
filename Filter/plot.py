from matplotlib import pyplot as plt
from scipy import signal
import os

here = os.path.dirname(os.path.abspath(__file__))  # find the working dir path
test_file = os.path.join(here, 'data.txt')        # create correct dir path

y = [0 for i in range(100)]
R = 0.97
data = open(test_file)
x = data.read()
x = x.split()

# convert ASCII number to float value
for i in range(0, len(x)):
    x[i] = float(x[i])

# apply IIR filter
for n in range(0, len(x)):
    if n == 0:
        y[n] = x[n]
    else:
        y[n] = x[n] - x[n-1] + (R*y[n-1])

# Remove negative values
for i in range(0, len(y)):
    if y[i] < 0:
        y[i] = 0

print(y)
#plt.setp(x, '.g', label='data')
plt.plot(x, 'r', label="input data")
plt.plot(y, 'b', label='Filtered data')
plt.grid()
plt.legend()
plt.xlabel('Time')
plt.show()
