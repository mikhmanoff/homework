CC= g++
INFO= coverage.info
FLAGS= -Wall -Wextra -Werror -std=c++17
GCOV= --coverage
VALGRIND_COMMAND=valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./s21_containers_test


ifeq ($(shell uname -s), Linux)
PKG_CONFIG= $(shell pkg-config --libs check) -lcheck -lpthread -lrt -lm -lsubunit
else
PKG_CONFIG= $(shell pkg-config --libs --cflags check)
endif

all: test

style:
	clang-format -style=Google -n *.h ./tests/*

fix_style:
	clang-format -style=Google -i *.h ./tests/*

test: clean
	$(CC) $(FLAGS) -o s21_containers_test ./tests/*.cpp -lgtest $(PKG_CONFIG)
	./s21_containers_test

gcov_report: clean
	$(CC) $(FLAGS) $(GCOV) -o gcov_report ./tests/*.cpp -lgtest $(PKG_CONFIG)
	./gcov_report
	lcov -t "gcov_report" -o $(INFO) -c -d . --no-external #--ignore-errors inconsistent
	genhtml -o coverage $(INFO) #--ignore-errors inconsistent
	open coverage/index.html

fsanitize: clean
	$(CC) $(FLAGS) -fsanitize=address -o s21_containers_test ./tests/*.cc -lgtest $(PKG_CONFIG)
	./s21_containers_test

valgrind:
	$(CC) $(FLAGS) -o s21_containers_test ./tests/*.cpp -lgtest $(PKG_CONFIG)
	$(VALGRIND_COMMAND)


clean:
	rm -rf *.a gcov_report report *test coverage *.o *.gcda *.gcno *.info *.dSYM *.txt
