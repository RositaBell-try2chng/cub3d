#!/bin/sh

set -xe

# Fix me: why clang does not work?
# Fix me: enable sanitizers
gcc -I../mlx -g -o tester -pedantic -std=c99 tests.c \
    cub_parser.c \
    write_syscall.c \
    map.c \
    map_left_right_check.c \
    read.c \
    color.c \
    color_2.c \
    color_3.c \
    number.c \
    lines.c \
    chars.c \
    mem.c \
    arrayz.c \
    error.c \
    fd.c \
    line_parse.c \
;

# Names: io, ...
