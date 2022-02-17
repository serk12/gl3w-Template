#!/bin/bash
# -*- ENCODING: UTF-8 -*-

###########################################
################ functions ################
###########################################
function install() {
  sudo apt install -y libgl1-mesa-dev freeglut3-dev libglm-dev
}

function first_build() {
  git submodule update --init --recursive || exit
  cd libs/gl3w/
  mkdir -p build
  cd build
  cmake ..
  make -j 8 || exit
}


###########################################
################# script ##################
###########################################
# set path
parent_path=$( cd "$(dirname "${BASH_SOURCE}")" ; pwd -P )
cd "$parent_path"
# default values
FORCE=False
INSTALL=False
PROFILE=Debug
# use .env file
set -a
    [ -f .env ] && . .env
set +a
# parse command
COMMAND=$1
shift
# allow patter matching (regex)
shopt -s extglob;
while [[ $# -gt 0 ]]
do
    key="$1"
    case $key in
      -f|--force)
      FORCE=True
      ;;
      -r|Release)
      PROFILE=Release
      ;;
      --install)
      INSTALL=True
      ;;
    esac
    shift
done

# process all
# pre-build
cd "$parent_path"
case $COMMAND in
  "first-build")
  if [ $INSTALL == True ]; then
    install
  fi
  echo "start first build"
  first_build
  echo "building"
  FORCE=True
  ;;
  "clean")
  cd build
  rm -rf ./*
  ;;
esac

# build
cd "$parent_path"
case $COMMAND in
  ""|"build"|"gdb"|"first-build")
  cd build
  if [ $FORCE == True ]; then
    cmake -DCMAKE_BUILD_TYPE=${PROFILE} ..
  fi
  make -j 8 || exit
  ;;
  "doxygen")
  mkdir -p build/doc
  doxygen Doxyfile
  ;;
esac

#run
cd "$parent_path"
case $COMMAND in
  "run"|""|"build"|"first-build")
  cd "$parent_path"/build/code/
  ./Hanbei
  ;;
  "gdb")
  cd "$parent_path"/build/code/
  gdb ./Hanbei
  ;;
  "doxygen"|"doc")
  firefox ${parent_path}/build/doc/html/index.html
  ;;
esac
