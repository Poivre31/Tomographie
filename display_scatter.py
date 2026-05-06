import numpy as np
from matplotlib import pyplot as plt
from math import floor, ceil
import sys

data = open(sys.argv[1])
n = int(data.readline())

x = np.empty(n)
y = np.empty(n)

for i in range(n):
    x[i] = float(data.readline())
    y[i] = float(data.readline())
    

plt.xticks(range(floor(np.amin(x)), ceil(np.amax(x))+1))
plt.yticks(range(floor(np.amin(y)), ceil(np.amax(y))+1))
plt.grid()

plt.scatter(x,y)
plt.show()