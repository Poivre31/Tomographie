import numpy as np
from matplotlib import pyplot as plt
import sys

img = open("build/img.txt")
width = int(img.readline())
height = int(img.readline())

image = np.empty((height,width))

for i in range(height):
    for j in range(width):
        image[i,j] = float(img.readline())

fft = np.fft.fftshift(np.fft.fft2(image))
    
plt.plot(abs(np.fft.ifft(fft[256,...])))
plt.show()