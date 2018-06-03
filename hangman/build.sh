#!/bin/sh

set -e

for file in *.re; do
  TARGET_FILE=`echo $file | sed 's/re$/ml/'`
  refmt --parse re --print ml $file > $TARGET_FILE
done

ocamlbuild main.native
./main.native
