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
```bash

```
