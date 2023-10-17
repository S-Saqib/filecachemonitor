#!/bin/bash

NUMPAGES=10
FILENAME=foo
EXISTS=1
FSYNC=0

if [ -z "$1" ]; then
  FILENAME=foo
else
  FILENAME="$1"
fi

NUMPAGES=$(./filepagecount.sh $FILENAME)
echo Total No. of Pages = "$NUMPAGES"
if [ "$EXISTS" -eq 0 ]; then
  #sudo rm -rf $FILENAME
  dd if=/dev/urandom of=$FILENAME count=$NUMPAGES bs=4K conv=fsync > /dev/null 2>&1
  sudo ./pagestatus $FILENAME $NUMPAGES $FSYNC
  #sudo rm -rf $FILENAME
else
  #cat $FILENAME > /dev/null 2>&1;
  sudo ./pagestatus $FILENAME $NUMPAGES $FSYNC
fi
