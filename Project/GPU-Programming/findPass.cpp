//Marco Karier

#include"header.h"
#include<string>
#include<sstream>
#include<ostream>
#include<iostream>
using namespace std;

int PASSLEN = 0;
int numfound = 0;
int total = 0;

int main(int argc, const char ** args)
{
	if(argc < 2)
	{
		printf("not enough arguments\n");
		exit(-99);
	}
	total = argc-1;
	PASSLEN = strlen(args[1]);
	//printf("first strlen\n");
	char** passwords = (char **)calloc(total, sizeof(char *));
	char ** truePasswords = (char **)calloc(total, sizeof(char *));
	int i = 1;
	const char * temp = crypter((const char *)args[1]);
	
	int len = strlen(temp);
	//printf("second strlen\n");
	passwords[0] = (char *)calloc(len, sizeof(char));
	memmove(passwords[0], temp, len);
	printf("Password %d: %s\n", 0, passwords[0]);
	for(i =1; i < total; i++)
	{
	   temp = crypter((const char *)args[i+1]);
	   len = strlen(temp);
	   passwords[i] = (char *)calloc(len, sizeof(char));
	   memmove(passwords[i], temp, len);
	   printf("Password %d: %s\n", i, passwords[i]);
	}//end of for loop to get passwords
	clock_t begin = clock();

	getPasswords(total, passwords, &truePasswords);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	for(i = 0; i < total; i++)
	{
		printf("%d truePasswords: %s\n", i, truePasswords[i]);
	}
	printf("execution time %f\n", time_spent);
	cleanUp(argc, passwords, truePasswords);
	return 0;
}//end of main


void getPasswords(int args, char** truePasswords, char *** found)
{
	char * start = (char *)calloc(PASSLEN, sizeof(char));
	search(*found, truePasswords, start, 0, &args);
	free(start);
}//end of getPasswords()

int search(char** found, char** truePasswords, char* start, int pos, int * args)
{
	if(pos < PASSLEN)
	{
		char c = 'a';
		for( ; c <= 'z'; c++)
		{
			start[pos] = c;
			search(found, truePasswords,start, pos+1, args);
			if(numfound == total)
				return 2;
		}//end of for loop
		return 1;
	}//end of else statemnt
	else
	{
		//TODO:needs to look for the password and return what it found;
		const char * temp = crypter((const char *)start);
		int i = 0;
		if(!strcmp(start, "aaa"))
			printf("should find the thing: %s\n", temp);
		for(i = 0; i < total && numfound < total; i++)
		{
			if(found[i] == NULL)
			{
				if(!strcmp(temp, truePasswords[i]))
				{
					found[i] = (char *)calloc(PASSLEN +1, sizeof(char));
					memcpy(found[i], start, PASSLEN);
					numfound++;
				}//end of inner if
			}//end of outer if
		}//end of rorloop
		return 0;
	}//end of if
}//end of search

const char * crypter(const char * data)
{
	uint a, b, c, d;
	md5_verify((unsigned char *)data, (uint)strlen(data), &a, &b, &c, &d);
	std::stringstream s;
	s << std::hex << a << b << c << d;
	const char * temp = s.str().c_str();
	return temp;
}

void cleanUp(int num, char** passwords, char** truePasswords)
{
   int i;
   for(i = 0; i < total; i++)
   {
      free(passwords[i]);
      free(truePasswords[i]);
   }//end of for loop
   free(passwords);
   free(truePasswords);
}//end of cleanUp()
