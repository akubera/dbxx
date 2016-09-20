#
# test/Makefile
#

CXX ?= g++

# bandit may be found in current directory
BANDIT_HEADER_DIR ?= .

CFLAGS = -I.. -I${BANDIT_HEADER_DIR} -Wall -std=c++11

ODBC_FLAGS = $(or $(shell odbc-config --cflags 2>/dev/null),\
                  $(shell iodbc-config --cflags 2>/dev/null),)
ODBC_LIBS = $(or $(shell odbc-config --libs 2>/dev/null),\
                 $(shell iodbc-config --libs 2>/dev/null),)

.PHONY: all test clean test_odbc

all test: test_odbc

test_odbc: build/test_odbc
	$<

build/test_odbc: test_odbc.cpp
	$(info Building ODBC test...)
	${CXX} ${CFLAGS} ${ODBC_FLAGS} $< -o $@ ${ODBC_LIBS}

build/test_%: test_%.cpp
	${CXX} ${CFLAGS} $< -o $@


clean:
	rm -rf build/*
