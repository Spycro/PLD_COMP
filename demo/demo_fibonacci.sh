#!/bin/bash
cd "$(dirname "$0")"
(../build/ifcc ./Fibo_interactif.c | gcc -x assembler - -o ../build/Fibo_interactif) && ../build/Fibo_interactif