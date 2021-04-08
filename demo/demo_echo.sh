#!/bin/bash
cd "$(dirname "$0")"
(../build/ifcc ./echo.c | gcc -x assembler - -o ../build/echo) && ../build/echo