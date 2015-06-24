#
# Makefile
#

SYSNAME := $(shell uname)

# set compiler

ifeq (${SYSNAME},Darwin)
  CC = clang
  CXX = clang++
else
  CC = gcc
  CXX = g++
endif

.PHONY: all, clean, cleanall, test

all:
	cd build && CC=${CC} CXX=${CXX} cmake .. && make

install:
	cd build && make install all

test:
	ctest

clean:
	rm -fr build/CM*
	rm -fr build/src

cleanall:
	rm -rf build/*
