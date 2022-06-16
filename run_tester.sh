#!/bin/bash
make
gcc tester.c sources/utils/*.c\
 sources/builtins/*.c libs/libft/sources/*.c \
 -o test.out
./test.out