#!/bin/bash

# builds CalbaCraft with argument release, both (debug and release) or default debug

RED='\033[1;31m'
GREEN='\033[1;32m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

if ! command -v conan &> /dev/null; then 
    printf "${RED}Conan command not found. Please install using ${WHITE}pip3 install conan.${NC}\n" 
    exit -1
fi

SCRIPT_PATH=$(dirname $0)
pushd $SCRIPT_PATH/../ > /dev/null

mkdir -p build/
cd build/

build() {
    BUILD_TARGET=${1^}

    printf "${GREEN}Building CalbaCraft in $BUILD_TARGET mode${NC}\n"

    mkdir -p $1
    pushd $1 > /dev/null
    # run conan if conan has not been ran yet
    [ ! -f conanbuildinfo.cmake ] && 
        conan install ../../ -s build_type=$BUILD_TARGET --build=glad
    
    # run cmake configure if not ran yet
    [ ! -f CMakeCache.txt ] && 
        cmake ../../ -DCMAKE_BUILD_TYPE=$BUILD_TARGET

    cmake --build . --config $BUILD_TARGET -- -j $(nproc) || exit -1
    popd > /dev/null
}

# specify build type or default debug
if [ "$1" = "release" ]; then
    build "release"
elif [ "$1" = "both" ]; then
    build "release"
    build "debug"
else
    build "debug"
fi

popd > /dev/null
