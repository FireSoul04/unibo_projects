### 1.
cercadir.sh
```bash
#!/bin/bash
for file in /usr/include/*; do
    if [[ -d ${file} && -r ${file} && ${file} -nt /usr/include/stdio.h ]]; then
        echo ${file}
    fi
done
```

### 2.
cercafile.sh
```bash
#!/bin/bash
for file in /usr/include/?[c-g]*; do
    if [[ -e ${file} && (${#file} -lt 18 || ${#file} -gt 23) ]]; then
        echo ${file}
    fi
done
```

### 3.
cercadir2.sh
```bash
#!/bin/bash
for file in /usr/include/*; do
    if [ -d ${file} && -r ${file} -a ${file} -nt /usr/include/stdio.h ]; then
        echo ${file}
    fi
done
```

### 4.
cercadir3.sh
```bash
#!/bin/bash
for file in /usr/include/*; do
    if test -d ${file} && -r ${file} -a ${file} -nt /usr/include/stdio.h; then
        echo ${file}
    fi
done
```

### 22.
leggere.sh
```bash
#!/bin/bash
if exec {FD}< /usr/include/stdio.h; then
	while read -u ${FD} word1 word2 word3 word4; do
        	if [[ -n ${word3} ]]; then
                	echo "${word3}"
        	fi
	done
	exec {FD}>&-
fi
```

### 23.
leggerecaratteri.sh
```bash
#!/bin/bash
COUNTER=0
if exec {FD}< /usr/include/stdio.h; then
        while read -N 1 -u ${FD} -r LEGGERE; do
                COUNTER=$(( ${COUNTER} + 1 ))
        done
        exec {FD}>&-
        echo ${COUNTER}
fi;
```

### 24.
```bash
wc -c /usr/include/stdio.h
```

### 25.
```bash
leggitutto.sh
#!/bin/bash
if exec {FD}< mioFile.txt; then
        while read -u ${FD} word; [[ $? -eq 0 || -n ${word} ]]; do
                echo ${word}
        done
        exec {FD}>&-
fi
```

### 27.
```bash
./star.sh < asterischi.txt
```

star.sh
```bash
#!/bin/bash
while read -r A B C D; do
        echo "${D} ${C}"
done
```
