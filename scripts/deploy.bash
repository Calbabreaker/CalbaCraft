#!/bin/bash

# package executable and assets into CalbaCraft directory

SCRIPT_PATH=$(dirname $0)
pushd $SCRIPT_PATH/../

# build release first
bash scripts/build.bash release

mkdir -p CalbaCraft
cp -f build/release/bin/CalbaCraft CalbaCraft/
cp -rf assets/* CalbaCraft/
rm CalbaCraft/*.log

popd
