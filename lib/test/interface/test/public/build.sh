#!/bin/bash
F=public.c
I=./test/protected/test/private/test/knowhow
gcc -c ${F} -I${I}
