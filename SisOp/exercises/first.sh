#!/bin/bash

echo "1."
echo $USER
echo $HOME
echo $DISPLAY

echo "2."
env | grep HOME
env | grep USER
env | grep DISPLAY

echo "3."
PIPPO="$USER,$HOME,$DISPLAY"
echo "PIPPO=$PIPPO"

echo "4."
echo "Prima PIPPO=$PIPPO"
bash ./crea_var.sh
echo "Dopo PIPPO=$PIPPO"

echo "5."
echo "Prima PIPPO=$PIPPO"
source ./crea_var.sh
echo "Dopo PIPPO=$PIPPO"

echo "6."
OLD_PWD=$(pwd)
cd /
echo ~
cd $OLD_PWD

echo "7."
mkdir ~/A1/
mkdir ~/A1/B2/
mkdir ~/A1/B2/C3/
touch ~/A1/B2/C3/{1,2,3}.txt
mv ~/A1/B2/C3/*.txt ~/A1/B2/
cp ~/A1/B2/*.txt ~/A1/

echo "8."
cat ~/.*

echo "9."
ls /usr/include/linux/netfilter/nf_nat.h

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

echo "18."
mkdir BUTTAMI
touch ./BUTTAMI/A{B,b}C.txt

echo "19."
rm ./BUTTAMI/ABC.txt

echo "20."
rm -rf BUTTAMI

echo "21."
ls /usr/lib/*[1-3c-m]*.0
