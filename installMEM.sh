#!/bin/bash

cd src/Madgraph
./SetupMadgraph.sh

cd ../../
make clean
make -j8

cd config
source setConfig.sh

cd ../bin
make clean
make

cd ..
