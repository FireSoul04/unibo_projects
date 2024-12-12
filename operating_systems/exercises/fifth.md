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
```bash

```
