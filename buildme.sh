#!/bin/sh
gcc renomear.c -o renomear

echo "Running Tests..."

./renomear test1.txt test2.txt test3.txt pre--