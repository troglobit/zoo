#!/bin/sh
# Verify creation time (or mtime) of new archives is not way back in 1970
if [ x"${srcdir}" = x ]; then
    srcdir=.
fi
. ${srcdir}/lib.sh

test_teardown()
{
    rm "${ark}" "${ark}.zoo"
}

ark=$(mktemp /tmp/zooXXXX)
tme=$(date --iso)

zoo a "$ark" . || fail "failed creating archive"
# shellcheck disable=SC2010,SC2012
ls -l --time-style=long-iso "${ark}.zoo" | grep "$tme"
