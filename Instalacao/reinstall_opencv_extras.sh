#!/bin/bash

cd opencv-*
cd build

echo "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_"

cmake -D CMAKE_BUILD_TYPE=RELEASE \
	-D OPENCV_EXTRA_MODULES_PATH=~/modulo_extra \
	-D CMAKE_INSTALL_PREFIX=/usr/local \
	-D WITH_TBB=ON \
	-D WITH_V4L=ON \
	-D INSTALL_C_EXAMPLES=ON \
	-D WITH_OPENGL=ON \
	-D WITH_EIGEN=ON ..

make -j4

echo "***********************************"

sudo make install

echo "***********************************"

sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'

echo "***********************************"

sudo ldconfig

echo "OpenCV ready to be used"
