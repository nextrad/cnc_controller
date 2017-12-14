#!/bin/bash

#Open VLC in Mosaic mode

echo "VLC Starting in Mosaic Mode..."

cvlc --vlm-conf mosaic.conf --mosaic-width=1280 --mosaic-height=720 --mosaic-keep-picture --mosaic-rows=2 --mosaic-cols=2 --mosaic-position=0 --mosaic-order=1,2,3,4


