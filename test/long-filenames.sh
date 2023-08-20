#!/bin/sh
# Verify adding and extracting very long filenames
if [ x"${srcdir}" = x ]; then
    srcdir=.
fi
. ${srcdir}/lib.sh

test_teardown()
{
    rm -rf "$src"
    rm -rf "$dst"
    rm "${ark}" "${ark}.zoo"
}

ark=$(mktemp /tmp/zooXXXX)
dst=$(mktemp -d)
src=$(mktemp -d)

mkdir -p "$src/a"
mkdir -p "$src/b"
touch "$src/a/short.nm"
touch "$src/b/the-very-longest-name-of-all-time-quite-possibly-so-save-me-xyzzy-from-the-fooish-bar.txt"
touch "$src/b/HyperTech_Quantum_Algorithm_v2.1_CodeX_SuperComp_GeekEdition_Report2023.docx"
touch "$src/b/FooBarBazQuxQuuxCorgeGraultGarplyWaldoFredPlughXyzzyThud_Report2023.docx"
#tree "$src"

cd "$src"             || fail "failed cd $src"
zoo a "$ark" .        || fail "failed creating archive"
cd -                  || fail "failed cd -"
#ls -l "${ark}.zoo"
#zoo l "${ark}.zoo"

cd "$dst"             || fail "failed cd $dst"
zoo x "${ark}.zoo"    || fail "failed extracting files"
cd -                  || fail "failed cd -"
#tree "$dst"

diff -r "$src" "$dst" || fail "failed diffing src and dst"
