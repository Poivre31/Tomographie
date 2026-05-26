import numpy as np
from matplotlib import pyplot as plt
import sys

data = open(sys.argv[1])
n = int(data.readline())

x = np.empty(n)

for i in range(n):
    x[i] = float(data.readline())

title = str(sys.argv[2])


plt.plot(x)
plt.title(title)
plt.show()
