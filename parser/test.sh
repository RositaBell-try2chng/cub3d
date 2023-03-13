#!/bin/sh
set -xe

cc -pedantic -std=c99 main.c

./a.out map.cub

./a.out empty

./a.out just_newline

./a.out one
