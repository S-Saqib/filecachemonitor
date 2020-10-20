#!/bin/bash

NUMPAGES=20
FILENAME=foo
FSYNC=0

sudo rm -rf $FILENAME; dd if=/dev/urandom of=$FILENAME count=$NUMPAGES bs=4K conv=fsync > /dev/null 2>&1;
sudo ./pagestatus foo $NUMPAGES $FSYNC
sudo rm -rf $FILENAME