#!/bin/bash
OUT=$(./lanciaeprendipid.sh 2> /dev/null)
echo $OUT
for pid in $OUT; do
    kill -9 $pid
done
