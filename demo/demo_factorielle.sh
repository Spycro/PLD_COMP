#!/bin/bash
cd "$(dirname "$0")"
(../build/ifcc ./factorielle.c | gcc -x assembler - -o ../build/factorielle) && ../build/factorielle