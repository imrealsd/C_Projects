compile:
	gcc main.c sudoku.c -o app.out
run:
	./app.out
debug:
	gcc -g main.c sudoku.c -o debug.out
	gdb debug.out
	
clean:
	rm app.out
	rm debug.out 

test:
	gcc unit_test/src/unity.c unit_test/test_sudoku.c sudoku.c -o test.out
	./test.out 