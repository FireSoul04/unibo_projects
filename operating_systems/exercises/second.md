### 22.
```bash
touch con\ spazio.txt senzaspazio1.txt senzaspazio2.txt
```

### 23.
```bash
touch lancia.sh stampaargs.sh
```

lancia.sh
```bash
#!/bin/bash
./stampaargs.sh $# "$@"
```

stampaargs.sh
```bash
#!/bin/bash
for arg in "$@"; do
    echo $arg
done
```

```bash
./lancia.sh *spazio*
```

### 24.
```bash
touch lancia2.sh stampaargs2.sh
```

lancia2.sh
```bash
#!/bin/bash
NOMIFILES="$# $@"
./stampaargs2.sh
```

stampaargs2.sh
```bash
#!/bin/bash
for arg in $NOMIFILES; do
    echo $arg
done
```

```bash
./lancia2.sh *spazio*
```

### 25.
```bash
rm "con spazio.txt" senzaspazio1.txt senzaspazio2.txt
```

### 26.
```bash
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
```

### 27.
```bash
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
```

### 4.
```bash
touch chiama_fattoriale.sh fattoriale.sh
./chiama_fattoriale.sh
```

chiama_fattoriale.sh
```bash
#!/bin/bash
RISULTATO=$(./fattoriale.sh 5)
echo ${RISULTATO}
```

fattoriale.sh
```bash
#!/bin/bash
NUM=1
FATTORIALE=1
while (( ${NUM} <= $1 )); do
    FATTORIALE=$(( ${FATTORIALE}*${NUM} ))
    NUM=$(( ${NUM}+1 ))
done
echo ${FATTORIALE}
```

### 5.
```bash
touch chiama_fattoriale1.sh fattoriale1.sh
./chiama_fattoriale1.sh
```

chiama_fattoriale1.sh
```bash
#!/bin/bash
RIS=1
source ./fattoriale1.sh 5
echo ${RIS}
```

fattoriale1.sh
```bash
#!/bin/bash
if (( $1 > 1 )); then
    ((RIS=${RIS}*$1))
    source ./fattoriale1.sh $(( $1-1 ))
fi
```

### 6.
```bash
./script1.sh a b "c d" e f
```

script1.sh
```bash
#!/bin/bash
NUM=1
while (( $NUM <= $# )); do
    echo ${!NUM}
    (( NUM=${NUM}+1 ))
done
./script2.sh "$@"
```

script2.sh
```bash
#!/bin/bash
NUM=$#
while (( $NUM > 0 )); do
    echo ${!NUM}
    (( NUM=${NUM}-1 ))
done
```

### 7.
```bash
man echo
echo -e "vado a capo\nrimuovo il carattere a da parola\b \taggiungo un tab"
```

### 8.
```bash
echo -n "non vado a capo"
```

### 9.
```bash
ls
```

### 10.
script.sh
```bash
#!/bin/bash
for file in *; do
    echo "file is ${file}"
    ls -d ./${file}
done
```

### 11.
script.sh
```bash
#!/bin/bash
for file in *; do; echo "file is ${file}"; ls -d ./${file}; done
```

### 12.
script.sh
```bash
#!/bin/bash
for file in *; do echo "file is ${file}"; ls -d ./${file}; if [[ $? -ne 0 ]]; then echo "ls produce errore"; fi; done
```

### 13.
```bash
touch "alfa beta.txt"
./script.sh
```

### 14.
```bash
ls
```

### 15.
```bash
./triplette.sh
```

triplette.sh
```bash
#!/bin/bash
for file1 in *; do
    for file2 in *; do
        for file3 in *; do
            echo "(${file1};${file2};${file3})"
        done
    done
done
```

### 16.
```bash
./argomenti.sh 1 3 5 6
```

argomenti.sh
```bash
#!/bin/bash
PARI=""
DISPARI=""
i=0
for arg in "$@"; do
    if (( $i%2==0 )); then
        PARI="${PARI} ${arg}"
    else
        DISPARI="${DISPARI} ${arg}"
    fi
    (( i=$i+1 ))
done
ARGS="${PARI} ${DISPARI}"
echo ${ARGS}
```

### 17.
```bash
./argomenti.sh ;
```

### 18.
```bash
./sommaquadrati.sh
```

sommaquadrati.sh
```bash
#!/bin/bash
SUM=0
COUNTER=$#
for arg in $*; do
    (( SUM=${SUM}+(arg*arg) ))
    (( COUNTER=${COUNTER}+${COUNTER}-1 ))
done
(( RESULT=${SUM}-${COUNTER} ))
echo ${RESULT}
```

### 19.
```bash
./main.sh
```

main.sh
```bash
#!/bin/bash
source definisci.sh
./usa.sh
source elimina.sh
./usa.sh
```

definisci.sh
```bash
#!/bin/bash
export VAR=INIZIO
```

usa.sh
```bash
#!/bin/bash
echo ${VAR}
```

elimina.sh
```bash
#!/bin/bash
unset VAR
```
