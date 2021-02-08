#!/bin/bash

# builds and run CalbaCraft with argument release or default debug

SCRIPT_PATH=$(dirname $0)
pushd $SCRIPT_PATH/../

BUILD_TARGET=$1
if [ ! "$1" = "release" ]; then
    BUILD_TARGET="debug"
fi

# build first 
bash scripts/build.bash $BUILD_TARGET

# run from the assets folder
cd assets/
../build/$BUILD_TARGET/bin/CalbaCraft

popd
