#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct Word
{
	char * input;
	int count;
	struct Word * next;
}Word;


/*
This is a constructor for the Word data structure
*/
Word * construct(char * input);//
int compare(const void *, const void *);
int compareCount(const void *, const void *);

/*
This method frees the memory that was allocated for the Word data structure. 
*/
void clearWord(Word * word);


typedef struct LinkedList
{
	Word * head;
	int size;
}LinkedList;//end of LinkedList
/*
This is a LinkedList Constructor
*/
LinkedList * llconstruct();


/*
This is to printLine that is the "|---|--|" but change able so that i can adjust it easier later if need be.
*/
void printLine();


/*
This method is to print the word in the proper format "| english word|  count|" will call the printline mehthod
*/
void printWord(Word * word);


void printList(Word *);

void clearList(Word **);

void mergeList(LinkedList ** master, LinkedList ** add);
