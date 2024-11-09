# 1.
```bash
echo $USER
echo $HOME
echo $DISPLAY
```

# 2.
```bash
env | grep HOME
env | grep USER
env | grep DISPLAY
```

# 3.
```bash
PIPPO="$USER,$HOME,$DISPLAY"
echo "PIPPO=$PIPPO"
```

# 3.
```bash
echo "Prima PIPPO=$PIPPO"
bash ./crea_var.sh
echo "Dopo PIPPO=$PIPPO"
```

# 5.
```bash
echo "Prima PIPPO=$PIPPO"
source ./crea_var.sh
echo "Dopo PIPPO=$PIPPO"
```

# 6.
```bash
cd /
echo ~
```

# 7.
```bash
mkdir ~/A1/
mkdir ~/A1/B2/
mkdir ~/A1/B2/C3/
touch ~/A1/B2/C3/{1,2,3}.txt
mv ~/A1/B2/C3/*.txt ~/A1/B2/
cp ~/A1/B2/*.txt ~/A1/
```

# 8.
```bash
cat ~/.*
```

# 9.
```bash
ls /usr/include/linux/netfilter/nf_nat.h
```

# 10.
```bash
history
!2
```

# 11.
```bash
history
set +o history
ls
history
set -o history
```

# 12.
```bash
PIPPO=1
set -a
BAUDO=2
set +a
env | grep PIPPO
env | grep BAUDO
unset PIPPO BAUDO
```

# 13.
```bash
echo "echo PIPPO" >> ~/.bashrc
echo "echo BAUDO" >> ~/.profile
```

# 14.
```bash
ls /usr/lib/*plu*
```

# 15.
```bash
man ls
```

# 16.
```bash
ls -alh /usr/include/
```

# 17.
```bash
ls -dlhR /usr/include/
```

# 18.
```bash
mkdir BUTTAMI
touch ./BUTTAMI/A{B,b}C.txt
```

# 19.
```bash
rm ./BUTTAMI/ABC.txt
```

# 20.
```bash
rm -rf BUTTAMI
```

# 21.
```bash
ls /usr/lib/*[1-3c-m]*.0
```
