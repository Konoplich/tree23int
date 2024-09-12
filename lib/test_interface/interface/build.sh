#!/bin/bash
F=interface.c
I=./test/public/test/protected/test/private/test/knowhow
gcc -c ${F} -I${I}
