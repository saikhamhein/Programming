import numpy as np
import matplotlib.pyplot as plt

# testing


def cart2pol(x, y):
    rho = np.sqrt(x**2 + y**2)
    #phi = np.arctan2(y, x)
    # return(rho, phi)
    return(rho)


fs = 8000  # samples per sec (rading)
raw_fs = 24000  # raw_data sample (generating)

# not necessary generated for visual(plotting) purpose only
raw_samples = np.linspace(0, 1, raw_fs)
raw_data = np.sin(2*np.pi*1000*raw_samples) + 0.5 * \
    np.sin(2*np.pi*2000*raw_samples+3*np.pi/4)

# sample the signal with 8000hz fs,full 1sec i.e 8000 samples.We only need 8 samples
samples = np.linspace(0, 1, fs)
data = np.sin(2*np.pi*1000*samples) + 0.5 * \
    np.sin(2*np.pi*2000*samples+3*np.pi/4)


plt.subplot(3, 1, 1)
plt.plot(raw_data, label="raw_signal")
plt.xlim([0, 24])
plt.xlabel('Time[1/fs]')
plt.ylabel('Amplitude')
plt.legend()

plt.subplot(3, 1, 2)
plt.plot(data, label="sampled_signal")
plt.xlim([0, 8])
plt.xlabel('Time[1/fs]')
plt.ylabel('Amplitude')
plt.legend()

real = [[0 for i in range(8)] for i in range(8)]
for n in range(0, 8):
    for i in range(0, 8):
        real[n][i] = np.round(np.round(data[i], decimals=4)
                              * np.cos(2*np.pi*n*i/8), decimals=4)


imag = [[0 for i in range(8)] for i in range(8)]
for n in range(0, 8):
    for i in range(0, 8):
        imag[n][i] = np.round(np.round(data[i], decimals=4)
                              * np.sin(2*np.pi*n*i/8), decimals=4)

for i in range(0, 8):
    print("m="+str(i)+"   "+str(real[i]))
    print("m="+str(i)+"   "+str(imag[i]))

out = [0 for i in range(8)]


# for n in range(8):
for i in range(8):
    out[i] = cart2pol(np.sum(real[i]), np.sum(imag[i]))
print(out)

plt.subplot(3, 1, 3)
plt.stem(out, label="DFT", use_line_collection=True)
plt.xlabel('Freq [khz] ')
plt.ylabel('Amplitude')
plt.legend()
plt.show()
