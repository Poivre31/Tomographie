./build.sh
clear
./configure.sh
echo
./compute_sinogram.sh
./reconstruct_image.sh

exec bash
