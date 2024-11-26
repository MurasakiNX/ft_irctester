#!/bin/bash
dir=$(pwd)
valgrind -q --track-fds=yes --leak-check=full --show-leak-kinds=all --show-reachable=yes --fair-sched=yes ./irctester $1 $2