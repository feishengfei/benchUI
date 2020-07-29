#!/bin/bash

#Step into build dir
workdir=$(cd $(dirname $0); pwd)

pushd $1
for fname in `ls .`
do
  echo "$fname,"
  md5sum $fname
done
popd
