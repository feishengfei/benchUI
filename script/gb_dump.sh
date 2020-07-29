#! /usr/bin/env bash

localpath=`pwd`

export LD_LIBRARY_PATH=/home/shunya/zac/install_dump/libs
# export LD_LIBRARY_PATH=/home/shunya/zac/test_lib/libs/
export DUMP_ALL=1

if [ $# -ne 1 ]; then
	echo "Usage: gb_dump.sh <demo>"
	exit -1
fi

# clear kernel log message
echo > /var/log/messages

# run demo
pushd ${localpath}
rm -rf dumps/
rm -rf results/
./${1}

cp ./dumps/*/* ./dumps/
rm -r ./dumps/Untitled*
cp /var/log/messages ./dumps/
cp -r results/* ./dumps/

pushd ./dumps/
/bin/dumpdata_translate.py
popd

mkdir ./result/${1}
mv ./dumps ./result/${1}/
mv ./results ./result/${1}/

popd
