#!/bin/bash

# package executable and assets into CalbaCraft directory

SCRIPT_PATH=$(dirname $0)
pushd $SCRIPT_PATH/../ > /dev/null

# build release first
bash scripts/build.bash release|| exit -1

mkdir -p CalbaCraft
cp -f build/release/bin/CalbaCraft CalbaCraft/
cp -rf assets/* CalbaCraft/
rm CalbaCraft/*.log

popd > /dev/null
