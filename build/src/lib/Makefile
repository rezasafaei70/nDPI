#
# Simple non-autotools dependent makefile
#
# ./autogen.sh
# cd src/lib
# make Makefile
#
AR = ar
CC = gcc
RANLIB = ranlib
#
# Installation directories
#
PREFIX     = /usr
libdir     = ${exec_prefix}/lib
includedir = ${prefix}/include/ndpi
ifneq ($(OS),Windows_NT)
CFLAGS     += -fPIC -DPIC
endif
CFLAGS     += -I../include -Ithird_party/include -DNDPI_LIB_COMPILATION -Wno-attributes -W -Wall -Wno-unused-parameter -Wno-unused-function -Wno-address-of-packed-member  -O2 -Wno-attributes   
LDFLAGS    += 
LIBS       = -lm  

OBJECTS   = $(patsubst protocols/%.c, protocols/%.o, $(wildcard protocols/*.c)) $(patsubst third_party/src/%.c, third_party/src/%.o, $(wildcard third_party/src/*.c)) $(patsubst ./%.c, ./%.o, $(wildcard ./*.c))
HEADERS   = $(wildcard ../include/*.h)
NDPI_VERSION_MAJOR   = 4
NDPI_LIB_STATIC      = libndpi.a
NDPI_LIB_SHARED_BASE = libndpi.so
NDPI_LIB_SHARED      = $(NDPI_LIB_SHARED_BASE).4.7.0
NDPI_LIBS            = $(NDPI_LIB_STATIC) $(NDPI_LIB_SHARED)
USE_HOST_LIBGCRYPT   = 0

ifneq ($(USE_HOST_LIBGCRYPT),0)
TMP_OBJS := $(OBJECTS)
OBJECTS   = $(filter-out third_party/src/gcrypt_light.o,$(TMP_OBJS))
endif

ifneq ($(OS),Windows_NT)
OS := $(shell uname)
endif
BUILD_MINGW    		 = 

ifeq ($(OS),Darwin)
CC=clang
SONAME_FLAG=
else
ifneq ($(BUILD_MINGW),)
NDPI_LIB_SHARED_BASE = libndpi
NDPI_LIB_SHARED      = $(NDPI_LIB_SHARED_BASE)-4.7.0.dll
else
SONAME_FLAG=-Wl,-soname,$(NDPI_LIB_SHARED_BASE).$(NDPI_VERSION_MAJOR)
endif
endif

all: $(NDPI_LIBS)

ndpi_main.c: ndpi_content_match.c.inc

$(NDPI_LIB_STATIC): $(OBJECTS)
	   $(AR) rc $@ $(OBJECTS)
	   $(RANLIB) $@      

$(NDPI_LIB_SHARED): $(OBJECTS)
	$(CC) -shared -fPIC $(CFLAGS) $(SONAME_FLAG) -o $@ $(LDFLAGS) $(OBJECTS) $(LIBS)
	ln -fs $(NDPI_LIB_SHARED) $(NDPI_LIB_SHARED_BASE)
	ln -fs $(NDPI_LIB_SHARED) $(NDPI_LIB_SHARED_BASE).$(NDPI_VERSION_MAJOR)

%.o: %.c $(HEADERS) Makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -f $(NDPI_LIB_STATIC) $(OBJECTS) *.o *.so *.lo libndpi.so*

distdir:
	find . -type d | xargs -I'{}' mkdir -p '$(distdir)/{}'
	find ../include -type f -name '*.h' \
		-a '!' -name 'ndpi_config.h' \
		-a '!' -name 'ndpi_define.h' | xargs -I'{}' cp '{}' '$(distdir)/{}'
	find . -type f -name '*.c' \
		-o -name '*.cc' \
		-o -name '*.c.inc' \
		-o -name '*.h' | xargs -I'{}' cp '{}' '$(distdir)/{}'

distclean: clean
	/bin/rm -f Makefile

check:
	true # nothing to do here

cppcheck:
	cppcheck --template='{file}:{line}:{severity}:{message}' --quiet --enable=all --force -I ../include *.c protocols/*.c

install: $(NDPI_LIBS)
	mkdir -p $(DESTDIR)$(PREFIX)$(libdir)
	cp $(NDPI_LIBS) $(DESTDIR)$(PREFIX)$(libdir)/
	cp -P $(NDPI_LIB_SHARED_BASE) $(DESTDIR)$(PREFIX)$(libdir)/
	cp -P $(NDPI_LIB_SHARED_BASE).$(NDPI_VERSION_MAJOR) $(DESTDIR)$(PREFIX)$(libdir)/
	mkdir -p $(DESTDIR)$(PREFIX)$(includedir)
	cp ../include/*.h $(DESTDIR)$(PREFIX)$(includedir)
