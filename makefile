CC=gcc
AR=ar
FLAGS= -Wall -g

all: frequency 

trie.o: trie.c trie.h 
	$(CC) $(FLAGS) -fPIC -c trie.c

main: main1.c trie.h 
	$(CC) $(FLAGS) -c main.c

frequency: frequency_libd main.o
	$(CC) $(FLAGS) -o frequency main.o ./trie.so

frequency_libd: trie.o 
	$(CC) -shared -o trie.so trie.o

.PHONY: clean all

clean:
	rm -f *.o all