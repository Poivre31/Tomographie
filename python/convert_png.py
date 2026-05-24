from PIL import Image
import sys
import numpy as np

image = Image.open("../resources/"+sys.argv[1]+ ".png")
array = np.array(image)
# plt.imshow(image)
# plt.show()

size = max(2**(image.width - 1).bit_length(),2**(image.height - 1).bit_length())
dx = size-image.width
dy = size-image.height

pad_left = dx // 2
pad_right = dx - pad_left

pad_top = dy // 2
pad_bottom = dy - pad_top

array = np.pad(array,((pad_top, pad_bottom), (pad_left, pad_right), (0, 0)),mode='constant',constant_values=0)

out = open(sys.argv[1]+ ".txt","w")
out.write(str(size)+"\n")
out.write(str(size)+"\n")
for i in range(0,size):
    for j in range(0,size):
        out.write(str(array[i,j,0])+"\n")

