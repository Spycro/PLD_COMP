#!/bin/bash
cd "$(dirname "$0")"
(../build/ifcc ./alphabet_quinconce.c | gcc -x assembler - -o ../build/alphabet_quinconce) && ../build/alphabet_quinconce