#!/bin/bash

# builds CalbaCraft with argument release, both (debug and release) or default debug

SCRIPT_PATH=$(dirname $0)
pushd $SCRIPT_PATH/../

mkdir -p build/
cd build/

build() {
    BUILD_TARGET=${1^}

    tput setaf 6
    printf "Building CalbaCraft in $BUILD_TARGET mode\n"
    tput sgr0

    mkdir -p $1
    cd $1
    # run conan if conan has not been ran yet
    if [ ! -f conanbuildinfo.cmake ]; then
        conan install ../../ -s build_type=$BUILD_TARGET --build=glad
    fi
    cmake ../../ -DCMAKE_BUILD_TYPE=$BUILD_TARGET
    make
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

popd
