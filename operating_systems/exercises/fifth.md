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
reversebizzarro.sh
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
errorigiudiziari.sh
```bash
#!/bin/bash
while read codiceVerdetto motivoVerdetto; do
        while read idProcesso codiceVerdettoProcesso; do
                if (( codiceVerdetto == codiceVerdettoProcesso )); then
                        while read nome cognome idProcessoDenuncia motivoDenuncia; do
                                if (( idProcesso == idProcessoDenuncia )); then
                                        echo "${nome} ${cognome} ${motivoDenuncia} ${motivoVerdetto}"
                                        break
                                fi
                        done < denunce.txt
                fi
        done < processi.txt
done < verdetti.txt
```

### 43.
```bash
wget http://www.cs.unibo.it/\~ghini/didattica/sistemioperativi/ESERCIZI/esprcond_errato.sh
```

### 44.
esprcond_errato.sh
```bash
#!/bin/bash
if [[ -e /usr/include/stdio.h ]]; then echo esiste; fi
```

### 45.
```bash
head -n 5 /usr/include/stdio.h | tail -n 3
```

### 46.
```bash
tail -n 4 /usr/include/stdio.h | cut -b -3
```

### 47.
```bash
read A; read B; echo "${B}"; echo "${A}"
```

### 48.
```bash
read A &> /dev/null
```

### 49.
```bash
while read A; do echo "${#A}"; done;
```

### 50.
```bash
( head -n 5 /usr/include/stdio.h | tail -n 3; tail -n 4 /usr/include/stdio.h | cut -b -3 ) | ( read A; read B; echo "${B}"; echo "${A}"; read A &> /dev/null; while read A; do echo "${#A}"; done; )
```

### 51.
```bash
#!/bin/bash
if (( $# != 1 )); then
        echo Need an argument
        exit 1
fi
TIME=$1
if [[ $TIME -le 0 ]]; then
        echo The time needs to be a positive number
        exit 1
fi
while (( $TIME > 0 )); do
        echo -n ". $$"
        sleep 1
        TIME=$((TIME-1))
done
echo ""
```

### 52.
```bash
./puntini.sh 35

bg
fg

bg
kill -9 $!
```

### 53.
```bash
./puntini.sh 35 &
kill -SIGKILL $!
```

### 54.
lanciaekilla.sh
```bash
#!/bin/bash
OUT=$(./lanciaeprendipid.sh 2> /dev/null)
echo $OUT
for pid in $OUT; do
    kill -9 $pid
done
```

lanciaeprendipid.sh
```bash
#!/bin/bash
for ((i=0; i <= 10; i++)); do
    ./puntini.sh 3 >&2 & echo -n "$! "
done
```

### 55.
```bash
./lanciaricorsivo 5
```

lanciaricorsivo.sh
```bash
#!/bin/bash
if (( $# != 1 )); then
    echo One argument required
    exit 1
fi
if [[ $1 -lt 0 ]]; then
    echo Argument should be a positive integer
    exit 2
fi

num=$1
if (( $num > 0)); then
    ./lanciaricorsivo.sh $((num - 1)) &
    childpid=$!
    echo $childpid
    wait $childpid
fi
```
