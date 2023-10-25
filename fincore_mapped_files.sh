MAPFILE="./randomread_map.txt"
TARGETDIR="/mnt/sheep/0/"
FINCORE="/cache-monitor/util-linux/fincore"
SERVERCACHEDPAGES="./server_cached_pages.txt"

while IFS=$'\t' read -r col1 col2; do
    SERVERFILE="$TARGETDIR""$col1"
    "$FINCORE" "$SERVERFILE" >> "$SERVERCACHEDPAGES"
done < "$MAPFILE"
