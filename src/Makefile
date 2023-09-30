CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -c -g
OS := $(shell uname)
TEST_FLAGS = $(shell pkg-config --cflags --libs check) -lm

all: clean test install

install: clean
	mkdir build
	cd SmartCalc && qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc/SmartCalc build
	build/SmartCalc

uninstall:
	rm -rf build

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0
	cp ./build/SmartCalc Archive_calc_v1.0
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

dvi:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" ../materials/doc/html/files.html
else
	xdg-open ../materials/doc/html/files.html
endif

test: s21_test.o s21_postfix.o s21_stack.o s21_bank.o
	$(CC) s21_test.o s21_postfix.o s21_stack.o s21_bank.o -o s21_test -L. $(TEST_FLAGS)
	./s21_test

s21_test.o: s21_test.c
	$(CC) $(CFLAGS) s21_test.c -o s21_test.o

s21_postfix.a: s21_postfix.o s21_stack.o
	ar rcs s21_postfix.a s21_postfix.o s21_stack.o
	ranlib s21_postfix.a

s21_bank.o: s21_bank.c
	$(CC) $(CFLAGS) s21_bank.c -o s21_bank.o

s21_postfix.o: s21_postfix.c
	$(CC) $(CFLAGS) s21_postfix.c -o s21_postfix.o

s21_stack.o: s21_stack.c
	$(CC) $(CFLAGS) s21_stack.c -o s21_stack.o

clean:
	rm -rf *.o *.a *.out *.info *.html *.gc* main gcov_report s21_postfix s21_test report build-SmartCalc-Desktop-Debug

gcov_report:
	$(CC) -fprofile-arcs -ftest-coverage s21_test.c s21_postfix.c s21_stack.c s21_bank.c -o gcov_report $(TEST_FLAGS)
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open_report:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/src/index.html
else
	xdg-open report/src/index.html
endif

clang:
	clang-format -n -style=google *.c *.h

clangI:
	clang-format -i -style=google *.c *.h

leak:
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./s21_test
else
	valgrind --leak-check=full -s --track-origins=yes ./s21_test
endif
	

rebuild: all
