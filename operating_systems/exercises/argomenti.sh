#!/bin/bash

PARI=""
DISPARI=""

i=0
for arg in "$@"; do
    if (( $i%2==0 )); then
        PARI="${PARI} ${arg}"
    else
        DISPARI="${DISPARI} ${arg}"
    fi
    (( i=$i+1 ))
done

ARGS="${PARI} ${DISPARI}"
