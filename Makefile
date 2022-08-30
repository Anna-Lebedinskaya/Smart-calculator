CC=gcc
CFLAGS=-Wall -Wextra -Werror
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
	LEAKS=CK_FORK=no valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./test
	testS=$(CC) -g test.c s21_SmartCalc.a $(LIBS) -o test
	# -lsubunit
else
	LIBS=-lcheck
	LEAKS=CK_FORK=no leaks --atExit -- ./test
	testS=$(CC) tests.c s21_SmartCalc.a $(LIBS) -o test
endif

all: clean s21_SmartCalc.a tests

install: dist
	cp -rf Mycalc.pro *.c *.h *.cpp *.ui ../build
	cd ../build; qmake Mycalc.pro
	make -C ../build
	cp -rf ../build/Mycalc.app  $(HOME)/Desktop

uninstall:
	@rm -rf $(HOME)/Desktop/Mycalc.app
	@rm -rf ../build

dvi: 
	open dvi.html

dist:
	mkdir -p ../build
	tar -cvzf ../build/Mycalc.tgz Makefile *.c *.h *.pro *.user *.cpp *.ui

tests: clean s21_SmartCalc.a
	$(testS)
	./test

gcov_report: s21_SmartCalc.a
	$(CC) --coverage -c calc.c stack.c
	ar rc s21_SmartCalc.a *.o
	$(CC) tests.c -L. s21_SmartCalc.a -lcheck -lpthread -lm -lgcov -o test_cov
	rm -rf *.o
	./test_cov
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	mkdir -p ./report
	genhtml -o report gcov_report.info
	open ./report/index.html

s21_SmartCalc.a:
	$(CC) -c calc.c -o calc.o
	$(CC) -c stack.c -o stack.o
	ar rcs s21_SmartCalc.a calc.o stack.o

clean:
	rm -rf *.0 *.a *.gcno *.gcda *.info *.out report *.dSYM *.gch *.o test2.out .vscode .DS_Store s21_SmartCalc.c.gcov test_cov CPPLINT.cfg s21_SmartCalc ../.DS_Store ../.vscode a.out

leaks: clean tests
	$(LEAKS)

codestyle:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=c calc.c stack.c calc.h stack.h
	rm -rf CPPLINT.cfg

CPPcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem calc.c stack.c calc.h stack.h

# CH: clean leaks codestyle CPPcheck
# 	rm -rf *.0 *.a *.gcno *.gcda *.info *.out report *.dSYM test2.out *.gch *.o .vscode .DS_Store a.out s21_SmartCalc.c.gcov test_cov CPPLINT.cfg s21_SmartCalc ../.DS_Store ../.vscode 