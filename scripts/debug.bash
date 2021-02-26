pushd $(dirname $0)/.. > /dev/null

bash scripts/build.bash Debug || exit -1
cd assets/
gdb ../build/debug/bin/CalbaCraft

popd > /dev/null
