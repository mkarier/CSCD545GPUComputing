#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 500
#define NUM_DELIMIT 23

char ** tokenize(char *, int *);

int isNotDelimit(char, char *, int);

void clearTokenList(char **, int);

void printTokenList(char **, int);

void strip(char *);

char * stortok_r(char *, char *, int, int *, int, char **);