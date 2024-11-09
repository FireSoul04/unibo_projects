#!/bin/bash

for name in $*; do
    echo ${name}
done
bash ./script2.sh $*
