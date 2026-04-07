#!/bin/bash

set -xe

clang -o main main.c -Werror -Wall -pedantic --std=c23
