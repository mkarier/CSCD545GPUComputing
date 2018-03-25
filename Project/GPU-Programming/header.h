#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <crypt.h>

typedef unsigned int uint;

void getPasswords(int args, char** truePasswords, char *** found);
int search(char** found, char** truePasswords, char* start, int pos, int * args);
void cleanUp(int num, char** passwords, char** truePasswords);
void md5_verify(unsigned char* data, uint length, uint *a1, uint *b1, uint *c1, uint *d1);
uint UNhex(unsigned char x);
const char * crypter(const char * data);

#endif