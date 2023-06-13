CC=gcc
INC=-I ../src/include -I/usr/local/include
LIBDPI=../src/lib/libndpi.a
CFLAGS+=-Wno-attributes -W -Wall -Wno-unused-parameter -Wno-unused-function -Wno-address-of-packed-member  -O2 -Wno-attributes
LDFLAGS+=
LIB=$(LIBDPI) -lm -lm 

TOOLS=metric_anomaly

all: $(TOOLS)

metric_anomaly: metric_anomaly.c Makefile $(LIBDPI)
	$(CC) $(CFLAGS) $(CPPFLAGS) -g $(INC) $(LDFLAGS) metric_anomaly.c -o metric_anomaly $(LIB)

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
