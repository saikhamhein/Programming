import numpy as np
from scipy.signal import butter, lfilter, freqz
import matplotlib.pyplot as plt
import os

here = os.path.dirname(os.path.abspath(__file__))  # find the working dir path
test_file = os.path.join(here, 'data.txt')        # create correct dir path


def butter_lowpass(cutoff, fs, order=5):
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    b, a = butter(order, normal_cutoff, btype='low', analog=False)
    return b, a


def butter_lowpass_filter(data, cutoff, fs, order=5):
    b, a = butter_lowpass(cutoff, fs, order=order)
    y = lfilter(b, a, data)
    return y


# Filter requirements.
order = 5
fs = 350      # sample rate, Hz
cutoff = 25  # desired cutoff frequency of the filter, Hz

# Get the filter coefficients so we can check its frequency response.
b, a = butter_lowpass(cutoff, fs, order)

# Plot the frequency response.
w, h = freqz(b, a, worN=8000)
plt.subplot(2, 1, 1)
plt.plot(0.5*fs*w/np.pi, np.abs(h), 'b')
plt.plot(cutoff, 0.5*np.sqrt(2), 'ko')
plt.axvline(cutoff, color='k')
plt.xlim(0, 0.5*fs)
plt.title("Lowpass Filter Frequency Response")
plt.xlabel('Frequency [Hz]')
plt.grid()


# Demonstrate the use of the filter.
# First make some data to be filtered.
T = 5.0         # seconds
n = int(T * fs)  # total number of samples
t = np.linspace(0, T, n, endpoint=False)
# "Noisy" data.  We want to recover the 1.2 Hz signal from this.
data = np.sin(1.2*2*np.pi*t) + 1.5*np.cos(9*2*np.pi*t) + \
    0.5*np.sin(18.0*2*np.pi*t)

# open the file containing data
test = open(test_file)
test_data = test.read()
test_data = test_data.split()
for i in range(0, len(test_data)):
    test_data[i] = int(test_data[i])
# Filter the data, and plot both the original and filtered signals.
y = butter_lowpass_filter(test_data, cutoff, fs, order)

plt.subplot(2, 1, 2)
plt.plot(test_data, 'b-', label='data')
plt.plot(y, 'g-', linewidth=2, label='filtered data')
plt.xlabel('Time [sec]')
plt.grid()
plt.legend()

plt.subplots_adjust(hspace=0.35)
plt.show()
