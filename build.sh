rm -rf ./build
mkdir build
cd build
cmake ..
make
cd ..
./build/src/app/c/agario
