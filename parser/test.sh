#!/bin/sh
set -xe

trap 'rm -f tester' 0

./compile.sh

for file in tests/{map.cub,just_newline,empty,one}; do
	./tester "$file"
done
