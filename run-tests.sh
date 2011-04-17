#!/usr/bin/env bash

# MIN MAX COUNT
#ARGS="1000 16000 11"
ARGS="100 1000 11"

echo "Compile and run C code"
gcc src/matrix.c -O3 -o bin/matrix_c && bin/matrix_c $ARGS > out/c.output

echo "Compile and run Fortran code"
gfortran src/matrix.f -O3 -g -march=native -o bin/matrix_f && bin/matrix_f $ARGS > out/f.output

echo "Run Python code"
python src/matrix.py $ARGS > out/py.output

echo "Run Lisp code"
sbcl --script src/matrix.lisp $ARGS > out/lisp.output
