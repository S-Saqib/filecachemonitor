#echo 1 > /proc/sys/vm/drop_caches #page cache
#echo 2 > /proc/sys/vm/drop_caches #dentries and inodes
echo 3 > /proc/sys/vm/drop_caches #all
