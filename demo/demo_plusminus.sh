#!/bin/bash
cd "$(dirname "$0")"
(../build/ifcc ./plusminus.c | gcc -x assembler - -o ../build/plusminus) && ../build/plusminus
