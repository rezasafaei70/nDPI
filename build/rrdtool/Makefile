CC=gcc
INC=-I ../src/include -I/usr/local/include
LIBDPI=../src/lib/libndpi.a
CFLAGS+=-Wno-attributes -W -Wall -Wno-unused-parameter -Wno-unused-function -Wno-address-of-packed-member  -O2 -Wno-attributes
LDFLAGS+=
LIB=$(LIBDPI) -lm -lm   -lpthread

TOOLS=rrd_anomaly rrd_similarity

all: $(TOOLS)

rrd_anomaly: rrd_anomaly.c Makefile $(LIBDPI)
	$(CC) $(CFLAGS) $(CPPFLAGS) -g $(INC) $(LDFLAGS) rrd_anomaly.c -o rrd_anomaly $(LIB)

rrd_similarity: rrd_similarity.c Makefile $(LIBDPI)
	$(CC) $(CFLAGS) $(CPPFLAGS) -g $(INC) $(LDFLAGS) rrd_similarity.c -o rrd_similarity $(LIB)

clean:
	/bin/rm -f *.o $(TOOLS) *~

distclean: clean
	/bin/rm -f Makefile

distdir:
	find . -type f -name '*.c' \
		-o -name '*.txt' | xargs -I'{}' cp '{}' '$(distdir)/{}'

install:
	@echo -n ""

check:
	true # nothing to do here
