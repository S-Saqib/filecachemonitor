FILENAME=foo
if [ -z "$1" ]; then
  FILENAME=foo
else
  FILENAME="$1"
fi

file_size_in_bytes=$(ls -l $FILENAME | awk '{print $5}')
page_size=$(getconf PAGESIZE)
#file_size_in_pages=$((file_size_in_bytes/page_size));
file_size_in_pages=$(echo "scale=0; ($file_size_in_bytes + $page_size - 1) / $page_size" | bc)
echo $file_size_in_pages
