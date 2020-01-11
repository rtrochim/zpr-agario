#!/bin/sh

./clean.sh
g++ --coverage -o BlobTest -fprofile-arcs -ftest-coverage BlobTest.cpp UserBlobTest.cpp -L /usr/lib -I/usr/include
./BlobTest
gcov BlobTest.cpp UserBlobTest.cpp
lcov --capture --base-directory "../app/c" --no-external --directory . --output-file BlobTest.info
genhtml BlobTest.info --output-directory coverage
cp -r coverage ../../../bioweb
rm *.gcov