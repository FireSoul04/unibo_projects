#!/bin/bash
exec {FD}< /usr/include/stdio.h
while read -u ${FD} word1 word2 word3 word4; do
	if [[ -n ${word3} ]]; then
		echo "${word3}"
	fi
done
