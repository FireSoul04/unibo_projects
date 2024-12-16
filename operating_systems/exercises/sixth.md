### 32.
lanciacerca.sh
```bash
#!/bin/bash
./cerca.sh /usr/include/ '*std*.h'
```

cerca.sh
```bash
#!/bin/bash
if (( $# != 2 )); then
    echo "Need two arguments"
    exit 1
fi
FILE=$1
if [[ ! -d $FILE ]]; then
    echo "Argument not a directory"
    exit 1
fi
TOKEN=$2

find $FILE -name "$TOKEN"
```

### 33.
```bash
find /usr/include/ -mindepth 2 -name "*net.h"
```

### 34.
```bash
find /usr/include/ -type f -exec head -n 3 '{}' \;
```

### 35.
```bash
find /usr/include/ -type f -exec head -n 3 '{}' \; | cut -b -3
```

### 56.
scrivisustderr.sh
```bash
#!/bin/bash
while read A; do
    echo ${A%% *} 1>&2
    echo "evviva"
done
```

### 57.
separa.sh
```bash
#!/bin/bash
for FILE in ${PATH//:/ }; do
    COUNT=0
    for ELEM in ${FILE//// }; do
        COUNT=$((COUNT + 1))
    done
    echo $FILE $COUNT
done
```

### 58.
backslash.sh
```bash
#!/bin/bash
while read A; do
    A=${A//'*'/'\*'}
    A=${A//'?'/'\?'}
    A=${A//'['/'\['}
    A=${A//']'/'\]'}
    echo $A
done
```

### 59.
separanomi.sh
```bash
#!/bin/bash
OUT=""
for FILE in ${PATH//:/ }; do
    for DIR in ${FILE//// }; do
        OUT="${OUT} ${DIR}"
    done
done
echo "$OUT"
```
