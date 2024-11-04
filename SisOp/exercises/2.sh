#!/bin/bash

echo "10."
history
#!2

echo "11."
history
set +o history
ls
history
set -o history

echo "12."
PIPPO=1
set -a
BAUDO=2
set +a
env | grep PIPPO
env | grep BAUDO
unset PIPPO BAUDO

echo "13."
echo "echo PIPPO" >> ~/.bashrc
echo "echo BAUDO" >> ~/.profile

echo "14."
ls /usr/lib/*plu*

echo "15."
man ls

echo "16."
ls -alh /usr/include/

echo "17."
ls -dlhR /usr/include/
