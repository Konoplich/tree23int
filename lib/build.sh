#!/bin/bash
F=knowhow.c
I=./test_interface/interface/test_public/public/test_protected/protected/test_private/private/test_knowhow/knowhow
gcc -shared -o libtree23int.so -fPIC ${F} -I${I}
cp libtree23int.so ..
cp libtree23int.h ..
