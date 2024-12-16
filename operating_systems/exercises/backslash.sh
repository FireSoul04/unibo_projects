#!/bin/bash
while read A; do
    A=${A//'*'/'\*'}
    A=${A//'?'/'\?'}
    A=${A//'['/'\['}
    A=${A//']'/'\]'}
    echo $A
done
