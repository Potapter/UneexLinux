move: move.c
	gcc -g -o0 move.c -o move

test: test_move test_protect

test_move: move
	@echo Hello, world! > in
	@strace -e fault=read:error=EACCES:when=1 ./move in test_out 2> test_1 || true
	@cat test_1 | grep "+++ exited with 127 +++" > trash
	@echo "TEST 1 SUCCESS"

	@echo Hello, world! > in
	@strace -e fault=close:error=EACCES:when=2 ./move in test_out 2> test_2 || true
	@cat test_2 | grep "+++ exited with 127 +++" > trash
	@echo "TEST 2 SUCCESS"

	@echo Hello, world! > in
	@strace -e fault=openat:error=EACCES:when=3 ./move in test_out 2> test_3 || true
	@cat test_3 | grep "+++ exited with 13 +++" > trash
	@echo "TEST 3 SUCCESS"

	@echo Hello, world! > in
	@strace -e fault=openat:error=EACCES:when=4 ./move in test_out 2> test_4 || true
	@cat test_4 | grep "+++ exited with 13 +++" > trash
	@echo "TEST 4 SUCCESS"

test_protect: move protect.c
	@gcc -shared -o protect.so protect.c
	@echo Hello, world! > test_PROTECT.txt
	@LD_PRELOAD=`pwd`/protect.so ./move test_PROTECT.txt test_out.txt
	@echo "PROTECT TEST SUCCESS"

clean:
	rm -f *.o move *.so test_* in *.txt trash
