PROG=executable
TEST=test
CC=g++
FLAGS=-Wall -Werror -std=c++11

$(PROG): main.o calculator.o parser.o helper.o
	$(CC) $(FLAGS) main.o calculator.o parser.o helper.o -o $(PROG)

$(TEST): tests.o calculator.o parser.o helper.o
	$(CC) $(FLAGS) tests.o calculator.o parser.o helper.o -o $(TEST)

main.o: main.cpp calculator.hpp parser.hpp helper.hpp
	$(CC) -c $(FLAGS) main.cpp

tests.o: tests.cpp calculator.hpp parser.hpp helper.hpp
	$(CC) -c $(FLAGS) tests.cpp

calculator.o: calculator.cpp calculator.hpp
	$(CC) -c $(FLAGS) calculator.cpp

parser.o: parser.cpp parser.hpp
	$(CC) -c $(FLAGS) parser.cpp

helper.o: helper.cpp helper.hpp
	$(CC) -c $(FLAGS) helper.cpp

clean:
	rm -f *.o $(PROG) $(TEST)
