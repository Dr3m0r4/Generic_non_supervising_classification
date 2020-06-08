#!/bin/bash

echo "do you want to execute the main project file ? (Y/n)"
read choice
if [[ $choice == "y" || $choice == "Y" ]]; then
  ./project
elif [[ $choice != "n" || $choice != "N" ]]; then
  while [[ 1 ]]; do
    echo "You fail !!"
  done
fi
