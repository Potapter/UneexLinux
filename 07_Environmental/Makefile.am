CFLAGS = -Wall -O0 -g -I. -lreadline

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

test: test_sha test_md

test_sha:
	@sha1sum src/rhasher.c > test1
	@echo 'SHA1 src/rhasher.c' | ./rhasher &> test2
	@sed -n '2p' test2 > test3
	@cat test1 | grep -f test3 > /dev/null
	@echo "=========== TEST1 SUCCEESS ==========="
	@rm test1 test2 test3

test_md:
	@md5sum src/rhasher.c > test1
	@echo 'MD5 src/rhasher.c' | ./rhasher &> test2
	@sed -n '2p' test2 > test3
	@cat test1 | grep -f test3 > /dev/null
	@echo "=========== TEST2 SUCCEESS ==========="
	@rm test1 test2 test3

gitclean:
	git clean -df
