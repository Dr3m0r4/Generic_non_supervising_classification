#!/bin/bash

cd build
cmake ..
make 2> errorlog

echo

echo "do you want to see the error log ? (y/n)"
read choice

if [[ $choice != "n" ]]; then
  less errorlog
else
  echo

  ./exec.sh

fi


cd ..
