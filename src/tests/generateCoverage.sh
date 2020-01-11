#!/bin/sh

./clean.sh
cp agario.db test.db
g++ -std=c++14 -fprofile-arcs -ftest-coverage BlobTest.cpp -L /usr/lib -I/usr/include -o BlobTest
g++ -std=c++14 -fprofile-arcs -ftest-coverage UserBlobTest.cpp -L /usr/lib -I/usr/include -o UserBlobTest
g++ -std=c++17 -fprofile-arcs -ftest-coverage GameTest.cpp -L /usr/lib -I/usr/include -I ../server/c -o GameTest
./BlobTest
./UserBlobTest
./GameTest
lcov --no-external --base-directory "../app/c" -c -d ./ -o test.info
genhtml test.info --output-directory coverage
cp -r coverage ../../../bioweb
rm test.db