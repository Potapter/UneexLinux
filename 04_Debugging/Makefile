range: range.c
		gcc -g -o0 range.c -w -o range

test: range
		gdb --args range 1 12 < gdb_scenario_1 | grep @@@ | cmp gdb_scenario_1_correct
		@ echo "Test 1 success!"

		gdb --args range -100 100 3 < gdb_scenario_2 | grep @@@ | cmp gdb_scenario_2_correct
		@ echo "Test 2 success!"

clean:
		rm -f range.o range a.out
