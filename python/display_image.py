import numpy as np
from matplotlib import pyplot as plt
import sys

n_image = (len(sys.argv) - 1) // 3

n_plot_h = n_image
n_plot_v = 1

if n_image > 3:
    n_plot_h = 2
    n_plot_v = 2
if n_image > 4:
    n_plot_h = 3
if n_image > 6:
    n_plot_h = 4
if n_image > 8:
    n_plot_v = 3

ax = None
img = open(sys.argv[1])
width_ref = int(img.readline())
height_ref = int(img.readline())

for k in range(1, n_image + 1):
    img = open(sys.argv[k])
    width = int(img.readline())
    height = int(img.readline())

    image = np.empty((height, width))

    for i in range(height):
        for j in range(width):
            image[i, j] = float(img.readline())

    if width == width_ref and height == height_ref:
        ax = plt.subplot(n_plot_v, n_plot_h, k, sharex=ax, sharey=ax)
    else:
        plt.subplot(n_plot_v, n_plot_h, k)
    gamma = float(sys.argv[k + 2 * n_image])
    title = str(sys.argv[k + n_image])
    if gamma == 1:
        plt.imshow(image, cmap="gray")
    else:
        plt.imshow(abs(image) ** (1 / gamma), cmap="gray")
    plt.title(title)

plt.show()
