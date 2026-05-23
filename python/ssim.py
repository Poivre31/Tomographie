from skimage.metrics import structural_similarity as ssim
from matplotlib import pyplot as plt
import numpy as np


img = open("build/a.txt")
width = int(img.readline())
height = int(img.readline())

image1 = np.empty((height, width))

for i in range(height):
    for j in range(width):
        image1[i, j] = float(img.readline())

img = open("build/b.txt")
width = int(img.readline())
height = int(img.readline())

image2 = np.empty((height, width))

for i in range(height):
    for j in range(width):
        image2[i, j] = float(img.readline())
        
print(ssim(image1,image2,data_range=1,gaussian_weights= True))

