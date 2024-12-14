#!/bin/bash
if (( $# != 1 )); then
    echo One argument required
    exit 1
fi
if [[ $1 -lt 0 ]]; then
    echo Argument should be a positive integer
    exit 2
fi

num=$1
if (( $num > 0)); then
    ./lanciaricorsivo.sh $((num - 1)) &
    childpid=$!
    echo $childpid
    wait $childpid
fi
