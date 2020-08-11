#!/bin/bash

path=$1

echo 'Source Files:'
find $path -type f -name "*.cpp"
find $path -type f -name "*.c"

echo " "
echo 'Header Files:'
find $path -type f -name "*.h"
find $path -type f -name "*.hpp"

echo " "
echo 'Scripts:'

find $path -type f -name "*.sh"

echo " "
echo 'Text Files:'

find $path -type f -name "*.txt"

echo " "
echo 'Directories:'

find $path -type d 

echo " "
echo 'Other Files:'

find $path -type f -not -name "*.txt" -not -name "*.cpp" -not -name "*.c" -not -name "*.hpp" -not -name "*.h" -not -name "*.sh"

