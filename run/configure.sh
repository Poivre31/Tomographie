rm config.txt
touch config.txt
echo Program configuration:

echo "Reference image (either name of a png image in ressources folder or one of three examples "shepp-logan", "rectangle", "ellipse"): "
read IMAGE
echo $IMAGE >> config.txt

echo "Physical size of the image:"
read IM_SIZE
echo $IM_SIZE >> config.txt

echo "Pixel size of the image (for generated images only, must be power of 2):"
read IM_PIX
echo $IM_PIX >> config.txt

echo "Physical size of the sensor:"
read SENS_SIZE
echo $SENS_SIZE >> config.txt

echo "Pixel size of the sensor (must be power of 2):"
read SENS_PIX
echo $SENS_PIX >> config.txt

echo "Number of projections (any):"
read N_PROJ
echo $N_PROJ >> config.txt
