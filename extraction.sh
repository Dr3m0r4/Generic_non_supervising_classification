#!/bin/bash

echo "enter a folder name :"
read folder_name

if [[ -d $folder_name ]]; then
  cd $folder_name
  cp -r * ..
  cd ..
  rm -rI $folder_name
fi
