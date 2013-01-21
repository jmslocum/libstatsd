lib_LTLIBRARIES = libstatsd.la
libstatsd_la_SOURCES = statsd.c statsd.h
include_HEADERS = statsd.h

bin_PROGRAMS = statsd-cli
statsd_cli_SOURCES = statsd-cli.c
statsd_cli_LDADD = libstatsd.la

CFLAGS += --std=gnu99
