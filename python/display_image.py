import numpy as np
from matplotlib import pyplot as plt
import sys

n_image = (len(sys.argv) - 1) // 2

n_plot_h = n_image
n_plot_v = 1

if n_image > 2:
    n_plot_h = 2
    n_plot_v = 2
if n_image > 4:
    n_plot_h = 3
if n_image > 6:
    n_plot_h = 4
if n_image > 8:
    n_plot_v = 3

for k in range(1, n_image + 1):
    img = open(sys.argv[k])
    width = int(img.readline())
    height = int(img.readline())

    image = np.empty((height, width))

    for i in range(height):
        for j in range(width):
            image[i, j] = float(img.readline())

    plt.subplot(n_plot_v, n_plot_h, k)
    gamma = float(sys.argv[k + n_image])
    if gamma == 1:
        plt.imshow(image, cmap="gray")
    else:
        plt.imshow(abs(image) ** (1 / gamma), cmap="gray")

plt.show()
