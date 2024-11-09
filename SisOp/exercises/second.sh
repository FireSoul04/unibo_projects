#!/bin/bash
echo "22."
touch con\ spazio.txt senzaspazio1.txt senzaspazio2.txt

echo "23."
touch lancia.sh stampaargs.sh
"lancia.sh"
"
#!/bin/bash
./stampaargs.sh $# "$@"
"
"stampaargs.sh"
"
#!/bin/bash
for arg in "$@"; do
    echo $arg
done
"
./lancia.sh *spazio*

echo "24."
touch lancia2.sh stampaargs2.sh
"lancia2.sh"
"
#!/bin/bash
NOMIFILES="$# $@"
./stampaargs2.sh
"
"stampaargs2.sh"
"
#!/bin/bash
for arg in $NOMIFILES; do
    echo $arg
done
"
./lancia2.sh *spazio*

echo "25."
rm "con spazio.txt" senzaspazio1.txt senzaspazio2.txt

echo "26."
mkdir BUTTAMI
cd BUTTAMI
touch "*" "**" "***" ";;"
ls BUTTAMI/*
for i in ./*; do
    touch "$i.txt"
done
cp -R /usr/include/ .
find . -type d
rm -rf ./include

echo "27."
mkdir BUTTAMI
cd BUTTAMI
touch "*" "**" "***" ";;"
ls BUTTAMI/*
for i in $(ls ./*); do
    touch "${i}.txt"
done
cp -R /usr/include/ .
find . -type d
rm -rf ./include

echo "4."
touch chiama_fattoriale.sh fattoriale.sh
"chiama_fattoriale.sh"
"
#!/bin/bash
RISULTATO=$(./fattoriale.sh 5)
echo ${RISULTATO}
"
"fattoriale.sh"
"
#!/bin/bash
NUM=1
FATTORIALE=1
while (( ${NUM} <= $1 )); do
    FATTORIALE=$(( ${FATTORIALE}*${NUM} ))
    NUM=$(( ${NUM}+1 ))
done
echo ${FATTORIALE}
"

echo "5."
"chiama_fattoriale1.sh"
"
RIS=1
source ./fattoriale1.sh 5
echo ${RIS}
"
"fattoriale1.sh"
"
if (( $1 > 0 )); then
    ((RIS=${RIS}*$1))
    source ./fattoriale1.sh $(( $1-1 ))
fi
"

echo "6."

