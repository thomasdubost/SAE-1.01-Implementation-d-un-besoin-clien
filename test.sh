#!/usr/bin/bash

./etudiant.out < inout/in-sp4-1.txt > inout/etudiant-out.txt
diff -sb --color=always inout/etudiant-out.txt inout/out-sp4-1.txt
