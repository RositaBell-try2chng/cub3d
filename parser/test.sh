#!/bin/sh
set -xe

cc -pedantic -std=c99 tests.c parser.c

./a.out map.cub

./a.out empty

./a.out just_newline

./a.out one
