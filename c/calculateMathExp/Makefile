PROG=executable
CC=g++
FLAGS=-Wall -Werror -std=c++11

all: $(PROG)

$(PROG): main.o functions.o
	$(CC) $(FLAGS) main.o functions.o -o $(PROG)

main.o: main.cpp functions.hpp
	$(CC) -c $(FLAGS) main.cpp

functions.o: functions.cpp functions.hpp
	$(CC) -c $(FLAGS) functions.cpp

clean:
	rm -f *.o $(PROG)