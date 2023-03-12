#!/bin/sh
set -xe

cc main.c

./a.out map.cub

./a.out empty

./a.out just_newline

./a.out one
