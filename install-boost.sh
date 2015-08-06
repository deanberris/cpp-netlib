#!/bin/sh
set -e
BOOST_VERSION=${BOOST_VER/./_}
if [ ! -d "${HOME}/${CXX}-boost_${BOOST_VERSION}" ]; then
  wget -O boost_${BOOST_VERSION}.tar.bz2 http://sourceforge.net/projects/boost/files/boost/${BOOST_VER}/boost_${BOOST_VERSION}.tar.bz2/download
  tar jxf boost_${BOOST_VERSION}.tar.bz2
  cd boost_${BOOST_VERSION}
  sh -x ./bootstrap.sh --with-toolset=$CC --prefix=$HOME/$CC-boost_${BOOST_VERSION}
  ./b2 --stagedir=. -j2 --build-type=complete --layout=tagged cxxflags='-std=c++11' install
  cd ..
  rm -rf boost_${BOOST_VERSION}
  rm -rf boost_${BOOST_VERSION}.tar.bz2
fi
