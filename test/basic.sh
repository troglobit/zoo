#!/bin/sh
set -x
export PATH=${PWD}/../src:$PATH

if [ -z "$srcdir" ]; then
    srcdir=.
fi

ark=`mktemp -u`
dst=`mktemp -d -p .`

zoo a $ark ${srcdir}/../doc/*

cd ${dst}
zoo x $ark
cd -

diff -r ${srcdir}/../doc ${dst}/doc

rm -rf ${dst}
rm $ark
