#!/bin/sh
# Check for uninitialized memory, leaks, etc.
if [ x"${srcdir}" = x ]; then
    srcdir=.
fi
. ${srcdir}/lib.sh
set +x

test_teardown()
{
    rm -rf "$dst"
    rm "${ark}" "${ark}.zoo"
}

check()
{
    valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all "$@"
}

ark=$(mktemp /tmp/zooXXXX)
dst=$(mktemp -d)

check zoo a "$ark" ${srcdir}/../man/* || fail "Memory leak when creating archive, error code $?"
check zoo a "$ark" ${srcdir}/../src/* || fail "Memory leak when adding to archive, error code $?"
check zoo l "$ark"                    || fail "Memory leak when listing archive, error code $?"
cd "$dst"                             || fail "failed cd $dst"
check zoo x "${ark}.zoo"              || fail "Memory leak when extracting archive, error code $?"
cd -                                  || fail "failed cd -"

diff -r ${srcdir}/../man ${dst}/man
