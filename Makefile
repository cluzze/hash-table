INC_DIR = include

CC 		= g++
CFLAGS 	= -c -Wall -Wextra -I$(INC_DIR)

all: main.o list.o
	$(CC) $^ -o main -lgtest -lpthread

main.o: src/main.cc
	$(CC) $(CFLAGS) $^

list.o: src/list.cc src/list.h
	$(CC) $(CFLAGS) $^

clean:
	rm *.o main src/*.gch

