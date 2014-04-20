#!/bin/bash

PIPE=$1

read line
if [ $line -eq 0 ]; then
  echo "WASP"
  /Users/ricca/MyCVS/dlv/dl -- < $PIPE
else
  echo "DLV"
  /Users/ricca/MyCVS/dlv/dl -- < $PIPE
fi

rm $PIPE
