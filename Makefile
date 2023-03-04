INC_DIR = include

CC 		= g++
CFLAGS 	?= -g -Wall -Wextra -I$(INC_DIR)

all: main.o list.o hash_table.o
	$(CC) $^ -o main -lgtest -lpthread

main.o: src/main.cc
	$(CC) $(CFLAGS) -c $^

list.o: src/list.cc
	$(CC) $(CFLAGS) -c $^

hash_table.o: src/hash_table.cc
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o main