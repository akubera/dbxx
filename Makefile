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

all:
	cd build && CC=${CC} CXX=${CXX} cmake .. && make

install:
	cd build && make install all

clean:
	rm -r build/CM*
	rm -r build/src

cleanall:
	rm -rf build/*
