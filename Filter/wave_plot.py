import matplotlib.pyplot as plt  # For ploting
import numpy as np  # to work with numerical data efficiently

fs = 44100  # samples per sec

f = 20  # frequency (Hz)
t = 1/f  # time in sec. Use 1/f to generate only one cycle

gain = 5
#f_2 = 2
#_3 = 3
samples = np.linspace(0, t, fs*t)
data = gain*np.sin(2*np.pi*f*samples)  # + np.sin(2*np.pi *
# f_2*samples) + np.sin(2*np.pi*f_3*samples)
plt.plot(samples, data, label=str(f)+'Hz')
plt.xlim([0, 1/f])
plt.xlabel('Time [sec]')
plt.ylabel('Amplitude')
plt.legend()
plt.show()
