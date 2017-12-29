t9: T9.o TrieNode.o LinkedListNode.o
	gcc -Wall -g -std=c11 -o t9 T9.o TrieNode.o LinkedListNode.o

LinkedListNode.o: LinkedListNode.c LinkedListNode.h
	gcc -Wall -g -std=c11 -c LinkedListNode.c

TrieNode.o: TrieNode.c TrieNode.h LinkedListNode.h
	gcc -Wall -g -std=c11 -c TrieNode.c

T9.o: T9.c TrieNode.h LinkedListNode.h
	gcc -Wall -g -std=c11 -c T9.c
