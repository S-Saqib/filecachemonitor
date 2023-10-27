MAPFILE="./sheepdog_unique_oids.txt"
TARGETDIR="/mnt/sheep/0/"
FINCORE="/util-linux/fincore"
SERVERCACHEDPAGES="./server_cached_pages.txt"

while IFS= read -r col1; do
    SERVERFILE="$TARGETDIR""$col1"
    "$FINCORE" "$SERVERFILE" >> "$SERVERCACHEDPAGES"
done < "$MAPFILE"
