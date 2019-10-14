#!/bin/sh

set -e

cd $(dirname $0)

make

while [ ! -d /media/2GB_HARMONY ]; do
  sleep 1
done

cp looptest.bin /media/2GB_HARMONY
sleep .5
eject /media/2GB_HARMONY

