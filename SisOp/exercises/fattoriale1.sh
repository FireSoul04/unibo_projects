if (( $1 > 0 )); then
    ((RIS=${RIS}*${1}))
    source ./fattoriale1.sh $(( $1-1 ))
fi
