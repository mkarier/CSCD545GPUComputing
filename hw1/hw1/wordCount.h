#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<errno.h>
#include"parser.h"
#include"LinkedList.h"

#define BUF_SIZE 4500
#define NUMBER_OF_THREADS 4
#define want_locks 0

pthread_mutex_t lock;

typedef struct storage
{
	LinkedList * list;
	char * string;
}storage;


Word * ReadInFile(char *, int *);

void findWord(char *, LinkedList *);


LinkedList * searchTokenList(char *);