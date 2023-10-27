MAPFILE="./sheepdog_unique_oids.txt"
TARGETDIR="/mnt/sheep/0/"
FINCORE="/util-linux/fincore"

while IFS= read -r col1; do
    SERVERFILE="$TARGETDIR""$col1"
    "$FINCORE" "$SERVERFILE"
done < "$MAPFILE"
