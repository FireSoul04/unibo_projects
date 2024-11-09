# 22.
```bash
touch con\ spazio.txt senzaspazio1.txt senzaspazio2.txt
```

# 23.
```bash
touch lancia.sh stampaargs.sh
```

```bash lancia.sh
#!/bin/bash
./stampaargs.sh $# "$@"
```

```bash stampaargs.sh
#!/bin/bash
for arg in "$@"; do
    echo $arg
done
```

```bash
./lancia.sh *spazio*
```

# 24.
```bash
touch lancia2.sh stampaargs2.sh
```

```bash lancia2.sh
#!/bin/bash
NOMIFILES="$# $@"
./stampaargs2.sh
```

```bash stampaargs2.sh
#!/bin/bash
for arg in $NOMIFILES; do
    echo $arg
done
```

```bash
./lancia2.sh *spazio*
```

# 25.
```bash
rm "con spazio.txt" senzaspazio1.txt senzaspazio2.txt
```

# 26.
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

# 27.
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

# 4.
```bash
touch chiama_fattoriale.sh fattoriale.sh
./chiama_fattoriale.sh
```

```bash chiama_fattoriale.sh
#!/bin/bash
RISULTATO=$(./fattoriale.sh 5)
echo ${RISULTATO}
```

```bash fattoriale.sh
#!/bin/bash
NUM=1
FATTORIALE=1
while (( ${NUM} <= $1 )); do
    FATTORIALE=$(( ${FATTORIALE}*${NUM} ))
    NUM=$(( ${NUM}+1 ))
done
echo ${FATTORIALE}
```

# 5.
```bash
touch chiama_fattoriale1.sh fattoriale1.sh
./chiama_fattoriale1.sh
```

```bash chiama_fattoriale1.sh"
RIS=1
source ./fattoriale1.sh 5
echo ${RIS}
```

```bash fattoriale1.sh
if (( $1 > 0 )); then
    ((RIS=${RIS}*$1))
    source ./fattoriale1.sh $(( $1-1 ))
fi
```

# 6.
```bash

```