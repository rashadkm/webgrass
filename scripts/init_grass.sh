#!/bin/bash

rm -rf $LOCATION/$MAPSET/.gislock;
export GRASS_PNG_AUTO_WRITE=TRUE; 
export GRASS_PNG_COMPRESSION=9; 
export GRASS_TRANSPARENT=TRUE; 
export GRASS_TRUECOLOR=TRUE; 
export LD_LIBRARY_PATH=/usr/lib/grass70/lib; 
export GISBASE=/usr/lib/grass70/; 
export GISRC=/home/mayank/Dropbox/Github/webgrass/.webgrass/rc; 
export PATH=/usr/lib/grass70/bin:/usr/lib/grass70/scripts:$PATH;
export GIS_LOCK=77;
g.gisenv;
#echo "answer"
#now=$($*);
#echo $($*);
$*;
echo $GISDBASE;