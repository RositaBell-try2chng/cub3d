#!/bin/sh
set -xe

trap 'rm -f tester' 0

./compile.sh

./tester map.cub &

sleep 0.5

pid=$(ps | grep tester | grep -v grep | sed 's/^ *//' | cut -f 1 -d ' ')

leaks "$pid"

kill "$pid"

# for file in tests/{map.cub,just_newline,empty,one}; do
# 	./tester "$file"
# done
