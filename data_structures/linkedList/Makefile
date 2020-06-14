PROG=executable
CC=gcc
FLAGS=-Wall -Werror -pedantic -std=c99

all: $(PROG)

$(PROG): main.o linkedList.o
	$(CC) $(FLAGS) main.o linkedList.o -o $(PROG)

main.o: main.c linkedList.h
	$(CC) -c $(FLAGS) main.c

linkedList.o: linkedList.c linkedList.h
	$(CC) -c $(FLAGS) linkedList.c

clean:
	rm -f *.o $(PROG)
