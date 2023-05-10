CC=gcc
CXX=g++
BUILD_MINGW=
EXE_SUFFIX=

SRCHOME=../../src

ifneq ($(OS),Windows_NT)
CFLAGS+=-fPIC -DPIC
endif
CFLAGS+=-g -I$(SRCHOME)/include -Wno-attributes -W -Wall -Wno-unused-parameter -Wno-unused-function -Wno-address-of-packed-member  -O2 -Wno-attributes -I/usr/include/json-c 
LIBNDPI=$(SRCHOME)/lib/libndpi.a
LIBS=$(LIBNDPI) -lpcap -lm -ljson-c 
LDFLAGS+=
HEADERS=$(SRCHOME)/include/ndpi_api.h $(SRCHOME)/include/ndpi_typedefs.h $(SRCHOME)/include/ndpi_protocol_ids.h
OBJS=unit
PREFIX?=/usr

ifneq ($(BUILD_MINGW),)

ifeq ($(DISABLE_NPCAP),0)
CFLAGS+=-I/home/boshra/project/nDPI/tests/unit/../windows/WpdPack/Include -I/home/boshra/project/nDPI/tests/unit/../windows/WpdPack/Include/pcap
else
CFLAGS+=-DDISABLE_NPCAP
endif

ifeq ($(DISABLE_NPCAP),0)

ifneq ($(BUILD_MINGW_X64),)
LIBS+=/home/boshra/project/nDPI/tests/unit/../windows/WpdPack/Lib/x64/wpcap.lib
else
LIBS+=/home/boshra/project/nDPI/tests/unit/../windows/WpdPack/Lib/wpcap.lib
endif

endif

LIBS+=-Wl,-Bstatic -lpthread -Wl,-Bdynamic
else
LIBS+=-pthread
endif

all: unit$(EXE_SUFFIX)

EXECUTABLE_SOURCES := unit.c
COMMON_SOURCES := $(filter-out $(EXECUTABLE_SOURCES),$(wildcard *.c ))

unit$(EXE_SUFFIX): $(LIBNDPI) unit.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) unit.o $(LIBS) -o $@

%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	/bin/rm -f *.o unit$(EXE_SUFFIX)
	/bin/rm -f .*.o.cmd .*.o.d
	/bin/rm -rf build

install:
	echo ""

distdir:

distclean: clean
	/bin/rm -f Makefile

check:
	true # nothing to do here, done by invoking tests/do-unit.sh
