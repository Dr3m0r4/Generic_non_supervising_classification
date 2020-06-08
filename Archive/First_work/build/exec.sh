#!/bin/bash

echo "do you want to execute the main file (y/n)"
read choice

echo

if [[ $choice != "n" ]]; then
  ./project
fi
