#!/bin/sh


# set -e -x

SPATH=$PATH

BRANCHES="
REL9_3_STABLE
REL9_4_STABLE
REL9_5_STABLE
REL9_6_STABLE
REL_10_STABLE
REL_11_STABLE
REL_12_STABLE
REL_13_STABLE
REL_14_STABLE
REL_15_STABLE
REL_16_STABLE
HEAD"

for br in $BRANCHES
do
	f=root/saves.test_parse/$br
	echo ==== $br ====
	PATH=$f/bin:$PATH
	initdb data-$br > logfile-$br 2>&1
	pg_ctl -l logfile-$br -D data-$br -w start >/dev/null 2>&1
	psql -t -q -f drive_parser_test.sql postgres
	pg_ctl -D data-$br stop >/dev/null 2>&1
	PATH=$SPATH
done

