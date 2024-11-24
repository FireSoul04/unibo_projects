#!/bin/bash
if exec {FD}< mioFile.txt; then
	while read -u ${FD} word; [[ $? -eq 0 || -n ${word} ]]; do
		echo ${word}
	done
	exec {FD}>&-
fi
