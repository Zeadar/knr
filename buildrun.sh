#!/bin/sh

# primary argument:
# source file containing main()

# secondary argument:
# d: execute with debugger
# v: execute with valgrind
# t: clock build time, don't execute
# no argument: execute

# rest of arguments are passed into ./out < /dev/stdin
# Don't try to feed arguments into gdb
# use: run < [stdin content] withing gdb instead

flags="-std=gnu99 -ggdb3 -Wall -Wextra -O0 -lm"
compiler="clang"

if [ "$2" = "d" ]; then
    $compiler $flags "$1" -o out
    shift 2
    gdb --args ./out "$@"
    # if [ -t 0 ]; then # stdin is a terminal — run interactively
    #     gdb --args ./out "$@"
    # else
    #     gdb --quiet --batch -ex "< /dev/stdin" --args ./out "$@" < /dev/stdin
    # fi
elif [ "$2" = "v" ]; then
    $compiler $flags "$1" -o out
    shift 2
    valgrind -- ./out "$@" < /dev/stdin 
elif [ "$2" = "t" ]; then
    time $compiler $flags "$1" -o out "$@"
else
    $compiler $flags "$1" -o out
    shift
     ./out < /dev/stdin "$@"
fi

rm -f out
