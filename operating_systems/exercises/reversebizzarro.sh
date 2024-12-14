#!/bin/bash
if (( $# <= 0 )); then
    echo Need at least an argument
    exit 1
fi
OUT=""
STR="$@"
i=$((${#STR} + 1))
while ((i >= 0)); do
    OUT="${OUT}${STR:i:1}"
    i=$((i-1))
done
echo "$OUT"
