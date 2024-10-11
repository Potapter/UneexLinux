CFLAGS = -Wall -fPIC

all: liboutput_static.a liboutput.so prog prog-a prog-so test

liboutput_static.a:	fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared -fPIC $^ -o $@

prog: prog.o const.o fun.o

prog-a: prog.o liboutput_static.a
	cc -Wall -fPIC -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -Wall -fPIC -L. $< -loutput -o $@

test: test0 test1 test3

test0: prog prog-a prog-so
	./prog > $@_prog.out 2>&1
	./prog-a > $@_prog-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > $@_prog-so.out 2>&1
	cmp $@_prog.out $@_prog-a.out
	cmp $@_prog.out $@_prog-so.out
	@echo "Test 0 pass"

test1: prog prog-a prog-so
	./prog a > $@_prog.out 2>&1
	./prog-a a > $@_prog-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so a > $@_prog-so.out 2>&1
	cmp $@_prog.out $@_prog-a.out
	cmp $@_prog.out $@_prog-so.out
	@echo "Test 1 pass"

test3: prog prog-a prog-so
	./prog a b c > $@_prog.out 2>&1
	./prog-a a b c > $@_prog-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so a b c > $@_prog-so.out 2>&1
	cmp $@_prog.out $@_prog-a.out
	cmp $@_prog.out $@_prog-so.out
	@echo "Test 3 pass"

fun.o:  outlib.h
prog.o:  outlib.h

clean:
	rm -f *.o *.out

distclean: clean
	rm -rf prog prog-a prog-so README liboutput_static.a liboutput.so
