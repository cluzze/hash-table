INC_DIR = include

CC 		= g++
CFLAGS 	?= -g -Wall -Wextra -I$(INC_DIR)

SRC = src/

all: main.o list.o hash_table.o
	$(CC) $^ -o main -lgtest -lpthread

tests: test_main.o list.o hash_table.o
	$(CC) $^ -o test_main -lgtest -lpthread

main.o: $(SRC)main.cc
	$(CC) $(CFLAGS) -c $^

test_main.o: $(SRC)test_main.cc
	$(CC) $(CFLAGS) -c $^

%.o: $(SRC)%.cc $(SRC)%.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o main $(SRC)*.gch