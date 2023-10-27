CLIENTCACHEDPAGES="client_cached_pages.txt"

rm "$CLIENTCACHEDPAGES"

/util-linux/fincore /sheepdog/sbd/dj0/largefile1/00000001/00000001 > "$CLIENTCACHEDPAGES"
