#!/bin/sh
# shellcheck disable=SC1090
if [ x"${srcdir}" = x ]; then
    srcdir=.
fi
. ${srcdir}/lib.sh

test_teardown()
{
    rm -rf "$dst"
    rm "${ark}" "${ark}.zoo"
}

ark=$(mktemp /tmp/zooXXXX)
src="$srcdir/.."
dst=$(mktemp -d)

cd "$src"          || fail "failed cd $src"
zoo a "$ark" man/* || fail "failed creating archive"

# Also verify adding more files work as intended.  32/64-bit problems
# with long in struct zoo_header caused "integrity check" issues.
zoo a "$ark" src/* || fail "failed adding src files"
cd -               || fail "failed cd -"

cd "$dst"          || fail "failed cd $dst"
zoo x "$ark"       || fail "failed extracting files"
cd -               || fail "failed cd -"

# Only verify man, 2nd src/* step verifies integrity only
diff -r "${srcdir}/../man" "${dst}/man"
