#!/bin/bash
FILENAME=6_File_1G

if [ -z "$1" ]; then
  FILENAME=6_File_1G
else
  FILENAME="$1"
fi

fincore "$FILENAME"
echo 1 > /proc/sys/vm/drop_caches
sleep 2
echo Dropped cache
fincore "$FILENAME"
$(make)
sleep 2
tail -1 "$FILENAME" > /dev/null
fincore "$FILENAME"
sleep 2
./filepagestatus.sh $FILENAME
sleep 2
fincore "$FILENAME"

#start=`date +%s%N`
#tail -1 "$FILENAME" > /dev/null
#end=`date +%s%N`
#echo Cache miss: reading time of the last line of a file: `expr $end - $start` ns
#
#sleep 10
#fincore "$FILENAME"

#start=`date +%s%N`
#tail -1 "$FILENAME" > /dev/null
#end=`date +%s%N`
#echo Cache hit: reading time of the last line of a file: `expr $end - $start` ns
