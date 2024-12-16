#!/bin/bash
OUT=""
for FILE in ${PATH//:/ }; do
    for DIR in ${FILE//'/'/ }; do
        OUT="${OUT} ${DIR}"
    done
done
echo "$OUT"
