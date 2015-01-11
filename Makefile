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
	rm -fr build/CM*
	rm -fr build/src

cleanall:
	rm -rf build/*
