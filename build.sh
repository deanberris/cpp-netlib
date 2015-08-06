#!/bin/sh
set -e

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE \
  -DBUILD_SHARED_LIBS=$DBUILD_SHARED_LIBS \
  -DCPP-NETLIB_ENABLE_HTTPS=$ENABLE_HTTPS \
  -DBOOST_ROOT=$HOME/$CC-boost_${BOOST_VER//./_} \
  -DCMAKE_CXX_FLAGS='-std=c++11' \
  ..
make -j2
make test
cd ..
