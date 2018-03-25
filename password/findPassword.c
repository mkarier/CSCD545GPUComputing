//Marco Karier
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <crypt.h>

typedef uint int;

char **readInPassWord();
char** getPasswords(const char** filePasswords);
void printTruePasswords(char** truePasswords);
void cleanUp(char** passwords, char** truePasswords);

int main()
{
   char** passwords = readInPassWord();
   
   printf("The First String: %s\n", passwords[0]);
   printf("The Second string: %s\n", passwords[1]);
   printf("The Third String: %s\n", passwords[2]);
   
   char** truePasswords = getPasswords((const char**) passwords);
   printf("first Password: %s", truePasswords[0]);
   printf("second password: %s", truePasswords[1]);
   printf("third password: %s", truePasswords[2]);
   printTruePasswords(truePasswords);
   cleanUp(passwords, truePasswords);

   return 0;
}//end of main

/*
   This method is to read in the password
*/
char** readInPassWord()
{
   int rfd;
   if(( rfd = open("pass.txt", O_RDONLY, 0)) < 0)
   {
      printf("Open failed");
   }
   char buffer[1024];
   char **rdPass = malloc(3*sizeof(char *));
   int i; 
   read(rfd, buffer, 1024);
   //printf("%s", buffer);
   char tempArray[3][1024];
   sscanf(buffer, "%s %s %s", tempArray[0], tempArray[1], tempArray[2]);
   //printf("tempArray[0]: %s\n", tempArray[0]);
   for(i = 0; i < 3; i++)
   {
      rdPass[i] = (char *)  malloc(strlen(tempArray[i]) * sizeof(char*));
      strcpy(rdPass[i], tempArray[i]);
   }//end of for loop
   //printf("The first String in reaInPassWord is %s\n", rdPass[0]);
   close(rfd);
   return rdPass;
}//end of readInPassWord()

char** getPasswords(const char** filePasswords)
{
   char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
   char *cryptTemp = (char*)malloc(strlen(filePasswords[0]) * sizeof(char));
   char *cryptTemp2 = (char*)malloc(strlen(filePasswords[1]) * sizeof(char));
   char *cryptTemp3 = (char*)malloc(strlen(filePasswords[2]) * sizeof(char));
   char** realPasswords =(char**) malloc(3 * sizeof(char*));
   realPasswords[0] = (char*) malloc(4 * sizeof(char));
   realPasswords[1] = (char*) malloc(4 * sizeof(char));
   realPasswords[2] = (char*) malloc(4 * sizeof(char));
   int first, second, third, fourth;
   int foundFirst = 1, foundSecond = 1, foundThird = 1;
   for(first = 0; first < 26; first++)
   {
      if(foundFirst == 0 && foundSecond == 0 && foundThird == 0)
      {
         break;
      }//end of if
      for(second = 0; second < 26; second++)
      {
         for(third = 0; third < 26; third++)
         {
            for(fourth = 0; fourth < 26; fourth++)
            {
               char temp[] = {alphabet[first], alphabet[second], alphabet[third], alphabet[fourth], '\0'};
               //printf("%s", temp);
               if(foundFirst == 1)
		         {
			         cryptTemp = crypt(temp, filePasswords[0]);
					if((strcmp(cryptTemp, filePasswords[0]) == 0))
					{
							 printf("It was able to find the first code. %s\n", temp);
							 temp[strlen(temp)-1] = '\n';
						strcpy(realPasswords[0], temp);
						foundFirst = 0;
					}//end of if statement
		         }//end of outer if statement
   	        if(foundSecond == 1)
   		     {
   			      cryptTemp2 = crypt(temp, filePasswords[1]);
                 	if((strcmp(cryptTemp2, filePasswords[1]) == 0))
                  {
   				      printf("It was able to find the second code. %s\n", temp);
   				      temp[strlen(temp)-1] = '\n';
   				      strcpy(realPasswords[1], temp);// strlen(temp));
                     foundSecond = 0;
                  }//end of if statement
   		      }//end of outter if statement
   		      if(foundThird == 1)
   		      {
   			      cryptTemp3 = crypt(temp, filePasswords[2]);
                  if((strcmp(cryptTemp3, filePasswords[2]) == 0))
                  {
   				      printf("It was able to find the third code. %s\n", temp);
   				      temp[strlen(temp)-1] = '\n';
   				      strcpy(realPasswords[2], temp);
                     foundThird = 0;
                  }//end of if statement
		      }//end of outter if statement
            }//end of fourth letter for loop
         }//end of third letter for loop
      }//end of second letter for loop
   }//end of first letter for loop
   if(foundFirst == 1 || foundSecond == 1 || foundThird == 1)
   {
      printf("Code not found.\n");
   }//end of if statement
   
   printf("it is outside the for loops\n");
   return realPasswords;
}//end of getPasswords()

void printTruePasswords(char** truePasswords)
{
  int wfd;
  wfd = open("plainpass.txt", O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
  int i;
  for(i = 0; i < 3; i++)
  {
	
       int bufferChars = strlen(truePasswords[i]);
	while(bufferChars > 0)
	{
       		int buffwritten = write(wfd, truePasswords[i], bufferChars);
		bufferChars = bufferChars - buffwritten;
	}
  }///end of for loop
  
  close(wfd);
}//end of printTruePasswords

void cleanUp(char** passwords, char** truePasswords)
{
   int i;
   for(i = 0; i < 3; i++)
   {
      free(passwords[i]);
      free(truePasswords[i]);
   }//end of for loop
   free(passwords);
   free(truePasswords);
}//end of cleanUp()
