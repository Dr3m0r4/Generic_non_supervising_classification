#!/bin/bash

echo "do you want to execute the main project file ? (Y/n)"
read choice
echo
if [[ $choice == "y" || $choice == "Y" ]]; then
  echo "with valgrind ? (Y/n)"
  read rechoice
  if [[ $rechoice == "y" || $rechoice == "Y" ]]; then
    valgrind ./KMeans
  elif [[ $rechoice == "n" || $rechoice == "N" ]]; then
    ./KMeans
  fi
elif [[ $choice != "n" && $choice != "N" ]]; then
  while [[ 1 ]]; do
    echo "You fail !!"
  done
fi
