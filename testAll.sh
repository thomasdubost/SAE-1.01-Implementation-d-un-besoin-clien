#!/usr/bin/bash

for file in inout/in-sp*-*.txt; do
    base="${file##*/}"                  
    num="${base#in-}"                   
    out="inout/etudiant-out-${num}"     
    ref="inout/out-${num}"              

    ./etudiant.out < "$file" > "$out"

    echo "Comparing $out with $ref"
    diff -sb --color=always "$out" "$ref"
done
