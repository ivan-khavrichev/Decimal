CC = gcc
STD = -std=c11
WFLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -lcheck

S21_LIB = s21_decimal.a
C_FILES = $(wildcard s21_*.c)
OBJ_FILES = $(patsubst %.c, %.o, $(C_FILES))

TEST_C_FILES = $(wildcard tests.c)

TEST_OBJ_FILES = $(patsubst %.c, %.o, $(TEST_C_FILES))

WSL_LINK_FLAGS = -lsubunit `pkg-config --cflags --libs check`

TRASH = $(wildcard *.o *.a *.gc* *.out tests test.info report .clang-format)

all: clean s21_decimal.a

s21_decimal.a: s21_decimal.o
	ar rc $(S21_LIB) $(OBJ_FILES)
	ranlib $(S21_LIB)

s21_decimal.o:
	$(CC) $(STD) -c $(WFLAGS) $(C_FILES)

test: clean s21_decimal.a
ifeq ($(shell uname -s), Linux)
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS)
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(S21_LIB) -o tests $(TEST_FLAGS) $(WSL_LINK_FLAGS)
	./tests
else
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS)
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(S21_LIB) -o tests  $(TEST_FLAGS) 
	./tests
endif

gcov_report: clean s21_decimal.a
ifeq ($(shell uname -s), Linux)
	$(CC) $(STD) --coverage $(C_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS) -o tests
else
	$(CC) $(STD) --coverage $(C_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) -o tests
endif
	./tests
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -n -style=google *.c *.h

correct_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -i -style=google *.c *.h

check_leaks: clean test
	leaks -atExit -- ./tests

clean:
	rm -rf $(TRASH)

rebuild: clean all
