#!/bin/bash

# builds and run CalbaCraft with argument release or default debug

pushd $(dirname $0)/.. > /dev/null

BUILD_TARGET=$1
if [ ! "$1" = "release" ]; then
    BUILD_TARGET="debug"
fi

# build first 
bash scripts/build.bash $BUILD_TARGET || exit -1

# run from the assets folder
cd assets/
../build/$BUILD_TARGET/bin/CalbaCraft

popd > /dev/null
