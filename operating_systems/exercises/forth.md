### 146.
lancia.sh
```bash
#!/bin/bash
export i=1
./figlio.sh
```

figlio.sh
```bash
#!/bin/bash
echo $$
if [[ ${i} -le 10 ]]; then
    i=$(( ${i} + 1 ))
    ./figlio.sh
fi
```

### 152.
```bash
#!/bin/bash
exec {FD}< "/usr/include/stdio.h"
while read -u ${FD} A B C D; do
    if [[ -n $C && -n ${C:1:1} ]]; then
        echo ${C:1:1}
    fi
done
```

### 164.
```bash
#!/bin/bash
SUM=0
IFS=","
while read A B C; do
    echo "$A, $C"
    SUM=$((SUM+B))
done < ./input1.txt
echo $SUM
```

### 160.
```bash
#!/bin/bash
NA=0
NB=0
ON_FIRST_SEQUENCE=0
VALID=0
STR=$1
for (( i = 0; $i < ${#STR} && $VALID == 0; i = $i + 1 )); do
        CHR=${STR:$i:1}
        if [[ $CHR == "A" && $ON_FIRST_SEQUENCE -eq 0 ]]; then
                NA=$((NA + 1))
        elif [[ $CHR == "B" ]]; then
                NB=$((NB + 1))
                ON_FIRST_SEQUENCE=1
        else VALID=1
        fi
done

if (( $NA == $NB && $NA != 0 && $VALID == 0 )); then
        echo "vero N=$NA"
else
        echo "falso"
fi
```

### 148.
```bash
#!/bin/bash
for FILE in /usr/include/std*; do
        NUMRIGA=0
        while read PAROLA; [[ $NUMRIGA -lt 4 ]]; do
                if [[ -n $PAROLA && $NUMRIGA -gt 0 ]]; then
                        echo ${PAROLA}
                fi
                NUMRIGA=$((NUMRIGA + 1))
        done < $FILE
done > ./output.txt
```
