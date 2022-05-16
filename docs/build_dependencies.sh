#!/bin/bash
echo "Build third_party/libfmt ..."
cd ../third_party/fmt/
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=./install
make -j8 && make install

echo "Build third_party/spdlog ..."
cd ../../spdlog/
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_PREFIX_PATH=../../fmt/build/install/lib/cmake/fmt ..
make -j8 && make install

echo "Build third_party/optional ..."
cd ../../optional/
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=./install ..
make -j8 && make install

echo "Build third_party/metis-5.1.0 ..."
cd ../../metis-5.1.0/
mkdir build
cd build
cmake -DGKLIB_PATH=../GKlib -DMETIS_LIBRARY_TYPE=SHARED -DCMAKE_INSTALL_PREFIX=./install ..
make -j8 && make install
