#!/bin/bash
set -e  # detener si ocurre un error

BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)

echo -e "\nEjecutando ./lonewolf ...\n"
./lonewolf
