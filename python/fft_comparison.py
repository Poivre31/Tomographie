import numpy as np
from matplotlib import pyplot as plt
import time
n = 4096;
a = 32;

image = np.empty((n,n))

for i in range(0,n):
    for j in range(0,n):
        if ((i - n / 2.) * (i - n / 2.) + (j - n / 2.) * (j - n / 2.) < a * a):
            image[i,j]=1;
        else:
            image[i,j]=0;

t1 = time.time()
fft = np.fft.fftshift(np.fft.fft2(image))
t2 = time.time()
print(t2-t1)

plt.imshow(abs(fft)**.45454545,cmap="gray")
plt.show()
