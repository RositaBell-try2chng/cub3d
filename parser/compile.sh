#!/bin/sh

set -xe

# Fix me: why clang does not work?
# Fix me: enable sanitizers
gcc -g -o tester -pedantic -std=c99 tests.c cub_parser.c
