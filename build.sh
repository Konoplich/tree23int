#!/bin/bash
rm ./ok
gcc main.c -o ok -L. -ltree23int -Wl,-rpath,. -I.
