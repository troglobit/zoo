#!/bin/sh
set -x

if [ -z "$srcdir" ]; then
    srcdir=.
fi

export PATH="$(realpath ../src):$PATH"

color_reset='\e[0m'
fg_red='\e[1;31m'
fg_green='\e[1;32m'
fg_yellow='\e[1;33m'
log()
{
    test=$(basename "$0" ".sh")
    printf "\e[2m[%s]\e[0m %b%b%b %s\n" "$test" "$1" "$2" "$color_reset" "$3"
}

sep()
{
    printf "\e[2m――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\e[0m\n"
}

say()
{
    log "$fg_yellow" • "$@"
}

skip()
{
    log "$fg_yellow" − "$*"
    exit 77
}

fail()
{
    log "$fg_red" ✘ "$*"
    exit 99
}

teardown()
{
    test_status="$?"

    if [ "$1" != "EXIT" ]; then
	print "Got signal, cleaning up"
    fi

    if type test_teardown > /dev/null 2>&1 ; then
	test_teardown
    fi

    say "EXIT: $test_status"
    exit $test_status
}

# props to https://stackoverflow.com/a/2183063/1708249
trapit()
{
    func="$1" ; shift
    for sig ; do
        trap '$func $sig' "$sig"
    done
}

trapit teardown INT TERM QUIT EXIT

if type test_setup > /dev/null 2>&1 ; then
    test_setup
fi
