SERVERCACHEDPAGES="./server_cached_pages.txt"

rm "$SERVERCACHEDPAGES"
./fincore_oids.sh > "$SERVERCACHEDPAGES"
