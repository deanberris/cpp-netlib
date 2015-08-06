#!/bin/sh
set -e

if [ ! -d "$HOME/$CC-boost_${BOOST_VER//./_}" ]; then
  wget -O boost_${BOOST_VER//./_}.tar.bz2 http://sourceforge.net/projects/boost/files/boost/${BOOST_VER}/boost_${BOOST_VER//./_}.tar.bz2/download
  tar jxf boost_${BOOST_VER//./_}.tar.bz2
  cd boost_${BOOST_VER//./_}
  sh -x ./bootstrap.sh --with-toolset=$CC --prefix=$HOME/$CC-boost_${BOOST_VER//./_}
  ./b2 --stagedir=. -j2 --build-type=complete --layout=tagged cxxflags='-std=c++11' install
  cd ..
  rm -rf boost_${BOOST_VER//./_}
  rm -rf boost_${BOOST_VER//._}.tar.bz2
fi
