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

.PHONY: all, clean, cleanall, docs, test

all:
	cd build && CC=${CC} CXX=${CXX} cmake .. && make

config:
	cd build && ccmake ..

install:
	cd build && make install all

docs:
	cd build && make doc

test:
	ctest

clean:
	rm -fr build/CM*
	rm -fr build/src

cleanall:
	rm -rf build/*
