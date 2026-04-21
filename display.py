import numpy as np
from matplotlib import pyplot as plt

img = open("img.txt")
width = int(img.readline())
height = int(img.readline())

image = np.empty((width,height))

for i in range(width):
    for j in range(height):
        image[i,j] = float(img.readline())
    

plt.imshow(image.T)
plt.show()