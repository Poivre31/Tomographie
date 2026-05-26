import numpy as np
from matplotlib import pyplot as plt

r0x = 0.2
r0y = 3
dx = 1.7
dy = 1

N = 16
x = np.empty(N * N)
y = np.empty(N * N)

for i in range(N):
    for j in range(N):
        tk1 = (j - r0y) / dy
        tk2 = (j + 1 - r0y) / dy
        x[i + j * N] = r0x + dx * tk1
        y[i + j * N] = r0y + dy * tk1

plt.scatter(x, y)

for i in range(N):
    for j in range(N):
        tl1 = (i - r0x) / dx
        tl2 = (i + 1 - r0x) / dx
        x[i + j * N] = r0x + dx * tl1
        y[i + j * N] = r0y + dy * tl1

plt.scatter(x, y)

plt.title("Intersections d'un rayon avec une grille 2D")
plt.grid()
plt.xlim(-2, 18)
plt.ylim(-2, 18)
plt.xticks(range(-2, 18))
plt.yticks(range(-2, 18))
plt.show()
