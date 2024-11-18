CFLAGS = -O2 -fprofile-arcs -ftest-coverage

lib_LTLIBRARIES = libbuf.la

libbuf.c: buf.h

gcov:
	gcov -o .libs libbuf -k -b
