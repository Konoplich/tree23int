#!/bin/bash
F=libtree23int.c
I=./test/interface/test/public/test/protected/test/private/test/knowhow
gcc -shared -o libtree23int.so -fPIC ${F} -I${I}
cp libtree23int.so ..
cp libtree23int.h ..
