#!/bin/sh

# primary argument:
# source file containing main()

# secondary argument:
# d: execute with debugger
# v: execute with valgrind
# t: clock build time, don't execute
# no argument: execute

flags="-std=gnu99 -ggdb3 -Wall -Wextra -O0 -lm"
compiler="gcc"

if [ "$2" = "d" ]; then
    $compiler $flags "$1" -o out && gdb ./out
elif [ "$2" = "v" ]; then
    $compiler $flags "$1" -o out && valgrind ./out
elif [ "$2" = "t" ]; then
    time $compiler $flags "$1" -o out
else
    $compiler $flags "$1" -o out && ./out
fi

rm -f out
