#
# Description:  Makefile for SIS 3610 IO Latch
#   This driver is specific to VxWorks BSPs and must be compiled
#   with access to vxWorks headers.
#
# adding the c792 library to 3610 & removing the refs to 3610
#  now update for the c775
# old make == INCDIR4     = $(CODALITE_BASE)/localDAQ/universeDma/
#    CPDA 3.06  has 
#   ./linuxvme/jvme/universeDma.h
#   ./linuxvme/jvme/universeDma.c
#
#  seems the LINUX version creates libjvme.so  which is in /lib so OK?
#
ARCH=Linux
DEBUG=1

#Check Operating system we are using
ifndef OSNAME
  OSNAME := $(subst -,_,$(shell uname))
endif

ifndef ARCH
	ARCH = VXWORKSPPC
ifndef WIND_BASE
	WIND_BASE=/site/vxworks/5.5/ppc
endif
endif

LIBDIR = $(CODA)/$(ARCH)/lib

ifeq ($(ARCH),VXWORKSPPC)
INCDIR=$(WIND_BASE)/target/h
CC = ccppc
LD = ldppc
DEFS = -mcpu=604 -DCPU=PPC604 -DVXWORKS -D_GNU_TOOL -DVXWORKSPPC
INCS = -Wall -fno-for-scope -fno-builtin -fvolatile -fstrength-reduce -mlongcall -I. -I$(INCDIR)
CFLAGS = -O $(DEFS) $(INCS)
endif

ifeq ($(ARCH),Linux)

LINUXVME_LIB	?= ${CODA}/extensions/linuxvme/libs
LINUXVME_INC	?= ${CODA}/extensions/linuxvme/include

CODALIB 	= $(CODA)/$(OSNAME)/lib
CODAINC 	= $(CODA)/common/include
INCS		= -I. -I${LINUXVME_INC}
LIBS		= -L${LINUXVME_LIB} -L. 
CFLAGS 		= -DJLAB

ifdef DEBUG
CFLAGS		+= -Wall -g
else
CFLAGS 		= -O2
endif

AR = ar
RANLIB = ranlib
DEPS = c775Lib.d
endif


ifeq ($(ARCH),Linux)
all: echoarch libc775.a links
else
all: echoarch c775Lib.o
endif

c775Lib.o: c775Lib.c c775Lib.h
	$(CC) -c $(CFLAGS) $(INCS) $(LIBS) -o $@ c775Lib.c



clean:
	rm -f  c775Lib.o libc775.so libc775.a

echoarch:
	echo "Make for $(ARCH)"

ifeq ($(ARCH),Linux)
libc775.a: c775Lib.o
	$(CC) -fpic -shared $(CFLAGS) $(INCS) $(LIBS) -o libc775.so c775Lib.c
	$(AR) ruv libc775.a c775Lib.o
	$(RANLIB) libc775.a


links:	libc775.a
	ln -sf $(PWD)/libc775.a $(LINUXVME_LIB)/libc775.a
	ln -sf $(PWD)/libc775.so $(LINUXVME_LIB)/libc775.so
	ln -sf $(PWD)/c775Lib.h $(LINUXVME_INC)/c775Lib.h


%.d: %.c
	@echo "Building $@ from $<"
	@set -e; rm -f $@; \
	$(CC) -MM -shared $(INCS) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.so $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPS)

endif
