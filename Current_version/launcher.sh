#!/bin/bash

if [[ ! -d build ]]; then
  mkdir build
fi
cd build
cmake ..
make 2> errorlog

echo

echo "do you want to see the error log ? (y/n)"
read choice

if [[ $choice == "y" || $choice == "Y" ]]; then
  less errorlog
elif [[ $choice == "n" || $choice == "N" ]]; then
  echo

  if [[ -f exec.sh ]]; then
    ./exec.sh
  else
    ./project
  fi

fi


cd ..
