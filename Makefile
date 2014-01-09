#
# Makefile
#

# set compiler
CC := gcc
CXX := g++


all:
	cd build && CC=${CC} CXX=${CXX} cmake .. && make

install:
	cd build && make install all

clean:
	rm -r build/CM*
	rm -r build/src

cleanall:
	rm -rf build/*
