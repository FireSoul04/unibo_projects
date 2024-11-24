#!/bin/bash
COUNTER=0
if exec {FD}< /usr/include/stdio.h; then
	while read -N 1 -u ${FD} -r LEGGERE; do
		COUNTER=$(( ${COUNTER} + 1 ))
	done
	exec {FD}>&-	
	echo ${COUNTER}
fi;
