#!/bin/bash
SUM=0
COUNTER=$#
for arg in $*; do
    (( SUM=${SUM}+(arg*arg) ))
    (( COUNTER=${COUNTER}+${COUNTER}-1 ))
done
(( RESULT=${SUM}-${COUNTER} ))
echo ${RESULT}
