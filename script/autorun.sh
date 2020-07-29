#!/bin/bash

if [ ! -d "result" ]; then
  echo "[RUN]: File(result) not exists, make it"
  mkdir result
  touch result/runlist
else 
  echo "[RUN]: File(result) exists"
  rm -rf ./result/*
fi

#echo "[RUN]: List file ===================="
for fname in `ls .`
do 
  if [[ "$fname" =~ ^es.* ]]; then
    echo "[RUN]: $fname  =======================>>>>>"
      if [ $1 == "dump" ]; then
        gb_dump.sh $fname
        mv ./result/*.bmp ./result/$fname/
        mv ./result/*.log ./result/$fname/
      else
        ./$fname
        echo "$fname" >> result/runlist
      fi
  fi
done
