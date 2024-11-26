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
