#!/bin/sh
rm -rf ext
mkdir ext
cd ext
git clone https://github.com/408b7f8b/helferlein.git
git clone https://github.com/RevolutionPi/piControl.git
git clone https://github.com/open62541/open62541.git
cd open62541
git checkout -b v1.0
mkdir build
cd build
cmake ..
make -j4
cd ../../ #wieder im ext-verzeichnis