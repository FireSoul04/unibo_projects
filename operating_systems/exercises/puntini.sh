#!/bin/bash
if (( $# != 1 )); then
    echo Need an argument
    exit 1
fi
TIME=$1
if [[ $TIME -le 0 ]]; then
    echo The time needs to be a positive number
    exit 1
fi
while (( $TIME > 0 )); do
    echo -n ". $$"
    sleep 1
    TIME=$((TIME-1))
done
echo ""
