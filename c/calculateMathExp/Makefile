PROG=executable
TEST=test
CC=g++
FLAGS=-Wall -Werror -std=c++11

all: $(PROG)

$(PROG): main.o functions.o
	$(CC) $(FLAGS) main.o functions.o -o $(PROG)

$(TEST): tests.o functions.o
	$(CC) $(FLAGS) tests.o functions.o -o $(TEST)

main.o: main.cpp functions.hpp
	$(CC) -c $(FLAGS) main.cpp

tests.o: tests.cpp functions.hpp
	$(CC) -c $(FLAGS) tests.cpp

functions.o: functions.cpp functions.hpp
	$(CC) -c $(FLAGS) functions.cpp

clean:
	rm -f *.o $(PROG) $(TEST)
