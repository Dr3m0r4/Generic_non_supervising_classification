#!/bin/bash

cd build
cmake ..
make 2> errorlog

echo

./project
cd ..
