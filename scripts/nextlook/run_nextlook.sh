#!/bin/sh
nohup ansible cobalt0 -m shell -a "nextlook -n 0" &
echo NeXtLook running on Node 0.
nohup ansible cobalt1 -m shell -a "nextlook -n 1" &
echo NeXtLook running on Node 1.
nohup ansible cobalt2 -m shell -a "nextlook -n 2" &
echo NeXtLook running on Node 2.


