#
# test/Makefile
#

CXX ?= g++

# bandit may be found in current directory
BANDIT_HEADER_DIR ?= .

CFLAGS = -I.. -I${BANDIT_HEADER_DIR} -Wall -std=c++11

.PHONY: all test clean test_odbc

all:
test: test_odbc

test_odbc: build/test_odbc
	$<

build/test_%: test_%.cpp
	${CXX} ${CFLAGS} $< -o $@

clean:
	rm -rf build/*
