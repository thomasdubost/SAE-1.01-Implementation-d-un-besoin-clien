#!/usr/bin/bash

./etudiant.out < inout/in.txt > inout/etudiant-out.txt
diff -sb --color=always inout/etudiant-out.txt inout/out.txt
