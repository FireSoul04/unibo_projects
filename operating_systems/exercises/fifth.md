### 28. 
```bash
cut -b 3-5,10-15 < ./test.txt
```

### 29.
```bash
cut -b 3-5,10-15 < ./test.txt | sed 's/ //g' | sed 's/\t//g' | sed 's/*//g'
```

### 30.
```bash
cut -b 3-5,10-15 < ./test.txt | sed 's/ //g' | sed 's/\t//g' | sed 's/*//g' | wc -c
```

### 35.
unasiunano.sh
```bash
#!/bin/bash
count=0
while read line; do
    if [[ $(($count % 2)) -eq 0 ]]; then
        echo "Output: ${line}"
    fi
    count=$((count + 1))
done
```

### 36.
random.sh
```bash
#!/bin/bash
COUNT=0
while [[ $((RANDOM % 10)) -ne 2 ]]; do
    COUNT=$((COUNT + 1))
done
echo "Times = $COUNT"
```

### 37.
elenco.sh
```bash
#!/bin/bash
NumFile=0
LungNomiDirectory=0
for file in *; do
    if [[ -d $file ]]; then
        LungNomiDirectory=$((LungNomiDirectory + ${#file}))
    elif [[ -e $file ]]; then
        NumFile=$((NumFile + 1))
    fi
done
echo "Lunghezza nomi directory=$LungNomiDirectory"
echo "Numero file=$NumFile"
```

### 38.
seconda.sh
```bash
#!/bin/bash
FILE=$1
if (( $# <= 0 || $# > 1 )); then
    echo One argument is required
    exit 1
fi
if [[ !( -e $FILE ) ]]; then
    echo File not found
    exit 1
fi
OUT=""
while read A B C; do
    OUT=${OUT}${B}
done < $FILE
echo ${OUT}
```

### 39.
```bash
cat input.txt | ./seleziona.sh
```

seleziona.sh
```bash
#!/bin/bash
grep -i A | wc -c
```

### 40.
```bash
for (( i=0; ls; i=i+1 )); do echo "${i}"; done
```
non produce errore se togliamo il punto

### 41.
```bash
#!/bin/bash
if (( $# <= 0 )); then
    echo Need at least an argument
    exit 1
fi
OUT=""
STR="$@"
i=$((${#STR} + 1))
while ((i >= 0)); do
    OUT="${OUT}${STR:i:1}"
    i=$((i-1))
done
echo "$OUT"
```

### 42.
```bash

```
