#
# File:
#    Makefile
#
# Description:
#    Makefile for the JLAB extensions to the GEFANUC Controller API
#
#
# $Date$
# $Rev$
#

ifndef LINUXVME_LIB
	LINUXVME_LIB	= $CODA/extensions/linuxvme/libs
endif
ifndef LINUXVME_INC
	LINUXVME_INC	= $CODA/extensions/linuxvme/include
endif

CROSS_COMPILE		=
CC			= $(CROSS_COMPILE)gcc
AR                      = ar
RANLIB                  = ranlib
CFLAGS			= -Wall -O2 -I${LINUXVME_INC} -I. -I/usr/include \
			  -L${LINUXVME_LIB} -L.

#  PROGS			= drgTst
PROGS			= drgTst

all: $(PROGS)


clean distclean:
	@rm -f $(PROGS) *~ *.so

%: %.c
	$(CC) $(CFLAGS) -o $@ $(@:%=%.c) $(LIBS_$@) -lrt -ljvme -lc775

.PHONY: all clean distclean
