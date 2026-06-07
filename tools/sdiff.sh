#!/bin/zsh
# sdiff.sh <symbol>  -> show instruction diff for symbol in materialman
SYM="$1"
cd /Users/zcanann/Documents/Projects/ffcc-grind-materialman
tools/objdiff-cli diff -p . -u main/materialman -o - --format json-pretty "$SYM" 2>/dev/null
