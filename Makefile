INC_DIR = include

CC 		= g++
CFLAGS 	?= -g -Wall -Wextra -I$(INC_DIR)
 
SRC = src/

all: hwk.o list.o hash_table.o
	$(CC) $(CFLAGS) $^ -o main

unit_tests: test_main.o list.o hash_table.o
	$(CC) $^ -o unit_tests -lgtest -lpthread

e2e_tests: e2e_main.o list.o hash_table.o
	$(CC) $^ -o e2e_tests -lgtest -lpthread

%.o: $(SRC)%.cc
	$(CC) $(CFLAGS) -c $^

%.o: $(SRC)%.cc $(SRC)%.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm main a.out *.o e2e_tests unit_tests hwk $(SRC)*.gch