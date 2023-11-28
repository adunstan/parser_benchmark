MODULE_big = drive_parser
OBJS = \
        $(WIN32RES) \
		drive_parser.o

EXTENSION = drive_parser
DATA = drive_parser--1.0.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

override CFLAGS +=  -Wno-unused -Wno-missing-prototypes

