#!/bin/bash

# builds CalbaCraft with argument release, both (debug and release) or default debug

RED='\033[1;31m'
GREEN='\033[1;32m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

if ! command -v conan &> /dev/null; then 
    printf "${RED}Conan command not found. Please install using ${WHITE}sudo pip3 install conan.${NC}\n" 
    exit -1
fi

pushd $(dirname $0)/.. > /dev/null

mkdir -p build/
cd build/

build() {
    BUILD_TARGET=${1^}

    printf "${GREEN}Building CalbaCraft in $BUILD_TARGET mode${NC}\n"

    mkdir -p $1
    pushd $1 > /dev/null

    [ ! -f conaninfo.txt ] && 
        CONAN_OPS="--build=glad"

    # run conan if conanfile.txt changed
    [ ! conaninfo.txt -nt ../../conanfile.txt ] && 
        echo "Conan file changed. Rerunning conan..." &&
        conan install ../../ -s build_type=$BUILD_TARGET $CONAN_OPS 
    
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
