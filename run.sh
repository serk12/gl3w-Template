#!/bin/bash
# -*- ENCODING: UTF-8 -*-

###########################################
################ functions ################
###########################################
function first_build() {
  git submodule update --init --recursive
  cd libs/gl3w/
  mkdir -p build
  cd build
  cmake ..
  make
  cd "$parent_path"
  cd build
  cmake ..
  make
}


###########################################
################# script ##################
###########################################
# set path
parent_path=$( cd "$(dirname "${BASH_SOURCE}")" ; pwd -P )
cd "$parent_path"
# default values
FORCE=False
# use .env file
set -a
    [ -f .env ] && . .env
set +a
# parse command
COMMAND=$1
PROFILE=Debug
shift
# allow patter matching
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
    esac
    shift
done

# process all
# build
case $COMMAND in
  "first-build")
  first_build
  ;;
  ""|"build"|"gdb")
  if [ $FORCE == True ]; then
    cd build
    cmake -DCMAKE_BUILD_TYPE=${PROFILE} ..
    cd ..
  fi
  cd build
  make || exit
  ;;
  "clean")
  cd build
  rm -rf ./*
  if [ $FORCE == False ]; then
    cmake -DCMAKE_BUILD_TYPE=${PROFILE} ..
  fi
  ;;
esac
#run
cd "$parent_path"
case $COMMAND in
  "run"|""|"build")
  ./build/code/Hanbei
  ;;
  "gdb")
  gdb ./build/code/Hanbei
  ;;
esac
