#!/bin/sh
set -x
export PATH=${PWD}/../src:$PATH

if [ -z "$srcdir" ]; then
    srcdir=.
fi

ark=`mktemp`
dst=`mktemp -d -p .`

zoo a $ark ${srcdir}/../doc/*

# Also verify adding more files work as intended.  32/64-bit problems
# with long in struct zoo_header caused "integrity check" issues.
zoo a $ark ${srcdir}/../src/*

cd ${dst}
zoo x $ark
cd -

# Only verify doc, 2nd src/* step verifies integrity only
diff -r ${srcdir}/../doc ${dst}/doc

rm -rf ${dst}
rm $ark
