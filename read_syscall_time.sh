fincore 6_File_1G
echo 1 >  /proc/sys/vm/drop_caches
sleep 10
echo Dropped cache
fincore 6_File_1G

start=`date +%s%N`
strace -f -e trace=all tail -1 6_File_1G > /dev/null
end=`date +%s%N`
echo Cache miss: reading time of the last line of a file: `expr $end - $start` ns

sleep 10
fincore 6_File_1G

start=`date +%s%N`
strace -f -e trace=all tail -1 6_File_1G > /dev/null
end=`date +%s%N`
echo Cache hit: reading time of the last line of a file: `expr $end - $start` ns
