#
# Makefile
#

DOXYGEN := doxygen

# assume source is in parent directory
DBXX_SOURCE ?= ../dbxx

.PHONY: all clean cleanall docs

all:
	${DOXYGEN} ${DBXX_SOURCE} 


clean:
	rm -r output/*

