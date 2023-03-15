#!/bin/sh
set -xe

trap 'rm -f tester' 0

cc -o tester -pedantic -std=c99 tests.c parser.c

for file in tests/{map.cub,just_newline,empty,one}; do
	./tester "$file"
done
