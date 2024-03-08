CC= gcc
LFLAGS= -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
TEST= ./unit_tests/test_*.c
all: s21_string.a gcov_report test
s21_string.a:
	$(CC) $(CFLAGS) -c s21_*.c
	ar rcs ./s21_string.a *.o

test: s21_string.a
	$(CC) $(CFLAGS) s21_*.c ./s21_string.a $(TEST) $(LFLAGS) -o test
	./test

gcov_report: s21_string.a
	$(CC) $(CFLAGS) --coverage s21_*.c $(TEST) $(LFLAGS) -o gcov_test
	./gcov_test
	lcov -t "gcov-test" -o test_report.info -c -d .
	genhtml -o report test_report.info
	rm -rf *.a *.gch *.o *.gcno gcov_test
	open ./report/index.html

clean:
	rm -rf *.a *.gch *.o *.gcno *.gcda

reduild:
	make clean
	make all

clang_n:
	clang-format -style=Google -n *.[ch]

clang_i:
	clang-format -style=Google -i *.[ch]