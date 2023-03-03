INC_DIR = include

CC 		= g++
CFLAGS 	= -c -Wall -Wextra -I$(INC_DIR)

all: main.o list.o hash_table.o
	$(CC) $^ -o main -lgtest -lpthread

main.o: src/main.cc
	$(CC) $(CFLAGS) $^

list.o: src/list.cc
	$(CC) $(CFLAGS) $^

hash_table.o: src/hash_table.cc
	$(CC) $(CFLAGS) $^

clean:
	rm *.o main src/*.gch