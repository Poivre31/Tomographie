import numpy as np
from matplotlib import pyplot as plt
import sys

img = open(sys.argv[1])
width = int(img.readline())
height = int(img.readline())

image = np.empty((height,width))

for i in range(height):
    for j in range(width):
        image[i,j] = float(img.readline())
    

plt.imshow(image,cmap='gray')
plt.show()