all: esub

esub: esub.c
	cc esub.c -Wall -o esub

test: esub test1 test2 test3

test1:
	@./esub '(a)(.*)(a)' '\3\2d\1' 'aaabbbabab' > esub_test_1
	@echo 'aaabbbabab' | sed -E 's/(a)(.*)(a)/\3\2d\1/' > sed_test_1
	@if cmp esub_test_1 sed_test_1 >/dev/null 2>&1;\
		then echo "---TEST 1 SUCCESS---";\
		else echo "---TEST 1 FAIL---";\
	fi

test2:
	@./esub '([ab])(b+)(a)' '\\\3\1' 'aababbaba' > esub_test_2
	@echo 'aababbaba' | sed -E 's/([ab])(b+)(a)/\\\3\1/' > sed_test_2
	@if cmp esub_test_2 sed_test_2 >/dev/null 2>&1;\
		then echo "---TEST 2 SUCCESS---";\
		else echo "---TEST 2 FAIL---";\
	fi

test3:
	@./esub '((ab+)+)' '\\\2\1\\' 'aaabbbabababaaabbbaab' > esub_test_3
	@echo 'aaabbbabababaaabbbaab' | sed -E 's/((ab+)+)/\\\2\1\\/' > sed_test_3
	@if cmp esub_test_3 sed_test_3 >/dev/null 2>&1;\
		then echo "---TEST 3 SUCCESS---";\
		else echo "---TEST 3 FAIL---";\
	fi

clean:
	rm -f esub *.o *_test_*
