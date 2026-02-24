#!/bin/bash

test -d build && rm -rf build 

mkdir build
cd build
cmake ..
make

echo -e "\nEjecutando ./lonewolf ...\n"
./lonewolf
