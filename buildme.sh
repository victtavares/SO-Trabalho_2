#!/bin/sh
gcc renomear.c -o renomear

echo "Copying the files from the testFiles folder to the current one!"
cp -a testFiles/. .
echo "Running Tests..."

# ./renomear

# ./renomear test1.txt
# ./renomear test1.txt pre--

#./renomear test1.txt test2.txt test3.txt test4.txt test5.txt test6.txt test7.txt prefix-

./renomear test1.txt test212.txt test3.txt test4.txt test5.txt test6.txt test7.txt bula-