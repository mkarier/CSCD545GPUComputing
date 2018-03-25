#include "parser.h"

char * stortok_r(char * input, char * delimit, int num_delimit, int *leftoff, int original_size, char ** svptr)
{
	char array[MAX];
	int index = 0, svtptr_index = *leftoff, firstWord = 1;
	char * ptr;
	//printf("input:%s\nsvptr%s\n\n", input, *svptr);
	if(input == NULL)
	{
		if(svtptr_index >= original_size -1)
			return NULL;
		ptr = *svptr;
		svtptr_index = 0;
		firstWord = 1;
	}//end of if
	else
	{
		/*while(isNotDelimit(*input, delimit, num_delimit) == 1 || *input == ' ')
		{
			input = input +1;
		}//*/
		ptr = input;
		//printf("%c\n", *ptr);
		//array[index++] = *ptr;
		//ptr = ptr+1;
	}
	//printf("ptr= %s\n", ptr);
	char * space = " ";
	char * end = "\n";
	char * end_point = strstr(ptr, end);
	if(end_point == NULL)
	{
		end = "\r";
		end_point = strstr(ptr, end);
		if(end_point == NULL)
		{
			end = "\0";
			end_point = strstr(ptr, end);
		}
		if(end_point == NULL)
		{
			perror("Still NULL\n");
			exit(-99);
		}
	}//end if jstatment for end point
	char * next_space = strstr(ptr, space);
	if(next_space == NULL)
		next_space = end_point;
	//printf("found next space%p\nRest of the word %s\n", next_space, next_space);
	if(*ptr == 'i' && *(ptr+1) == '\'' && *(ptr+2) == 'm')
	{
		//printf("special case\n");
		array[index++] = 'i';
		svtptr_index++;
		array[index++] = '\'';
		svtptr_index++;
		array[index++] = 'm';
		svtptr_index++;
		ptr = ptr+3;
	}//end of if*/
	while(index <= 1 && ptr != end_point)
	{
		while(((ptr != next_space) && (ptr != end_point) && (svtptr_index < original_size)) || firstWord)
		{
			//printf("index = %d \nptr's char:%c\n",index,  *ptr);
			if(*ptr == ' ')
				break;
			else if(isNotDelimit(*ptr, delimit, num_delimit))
			{
				array[index++] = *ptr;
				firstWord = 0;
			}
			else
			{
					//printf("%c: was delimit \n", *ptr);
			}
			ptr = ptr+1;
			svtptr_index++;
		
		}//end of while loop
		if(index < 2)
		{
			//ptr = next_space +1;
			//printf("index was less then 1\n");
			if(ptr == end_point)
				return NULL;
			next_space = strstr(ptr+1, space);
			if(next_space == NULL)
				next_space = end_point;
			ptr = ptr+1;
			index = 0;
			//firstWord = 1;
		}//end of if statment
	}//end of while loop
	if(ptr == end_point && index <= 1)
		return NULL;
	array[index] = '\0';
	char * word = calloc(index+1, sizeof(char));
	memmove(word, array, index);
	*svptr = ptr;
	
	*leftoff = svtptr_index;
	//char * word = array;
	//printf("array =%s\nword=%s\n", array,word);
	return word;
	
}

int isNotDelimit(char x, char * delimit, int num_delimit)
{
	int index = 0;
	for(index = 0; index < num_delimit; index++)
	{
		if((x == delimit[index]))
		{
			return 0;
		}//end of if statment
	}//end of for loop
	return 1;
}//end of isNotDelimit

char ** tokenize(char * input, int * countWords)
{
	if(input == NULL || strlen(input) == 0)
	{
		return NULL;
		//exit(-99);
	}
	int o_size = strlen(input);
	int leftoff = 0;
	char * temp = calloc(o_size+1, sizeof(char));
	memcpy(temp, input, o_size);
	char * ptr = temp;
	char * saveptr;
	char delimit[NUM_DELIMIT] = {'\t', '=','\"', '-', '!', ',', '+','\'', '(', ')', '?', '{', '}', '\r', '/', '\\', '<', '>', ':', '.', '*', '\n', '\0'};
	int count = 0;
	//printf("first call \n");
	char * str = stortok_r(ptr, delimit, NUM_DELIMIT, &leftoff, o_size, &saveptr);
	//char * str = strtok_r(ptr, delimit, &saveptr);
	if(str == NULL)
	{
		free(temp);
		return NULL;
	}
	
	//printf("end of first call: %s\n", str);
	char ** tokenList = calloc(2, sizeof(char *));
	tokenList[count] = calloc(strlen(str)+1, sizeof(char));
	memcpy(tokenList[count], str, strlen(str));
	count = 1;
	//printf("end of the first call\n");
	while(str != NULL)
	{
		free(str);
		//printf("in while loop\n");
		ptr = NULL;
		//int o_size = sizeof(tokenList);
		tokenList = realloc(tokenList, sizeof(char *) * (count+2));
		
		//printf("Calling strtok_r for the %d time.\n", count);
		str = stortok_r(ptr, delimit, NUM_DELIMIT, &leftoff, o_size, &saveptr);
		//str = strtok_r(ptr, delimit, &saveptr);
		if(str!= NULL)
		{
			tokenList[count] = calloc(strlen(str)+1, sizeof(char));
			memcpy(tokenList[count], str, strlen(str));
			count++;
		}
	}//end of while loop
	//printf("out of tokenize while loop \n");
	*countWords = count;
	//free(*input);
	free(temp);
	//printTokenList(tokenList, count);
	return tokenList;
}//end of tokenize

/*
This method is for debugging to make sure the at the array returned is properly formated.
*/
void clearTokenList(char ** list, int count)
{
	int i = 0;
	//printf("count %d\n", count);
	for(i = 0; i < count; i++)
	{
		//printf("%s\n", list[i]);
		free(list[i]);
	}
}//end of 

void printTokenList(char ** list, int count)
{
	int i = 0;
	//printf("count %d\n", count);
	for(i = 0; i < count; i++)
	{
		printf("%s\n", list[i]);
		//free(list[i]);
	}
}//end of printTokenList

void strip(char * str)
{
	int len = strlen(str) +1;
	int x = 0;
	while(x < len)
	{
		if(str[x] == '\r')
		{
			str[x] = '\n';
		}
		/*else if(str[x] == '\n')
		{
			str[x] = '\0';
		}//*/
		/*else if(str[x] == ' ')
		{
			str[x] = '\0';
		}//*/
		else
			str[x] = tolower(str[x]);
		x++;
	}//end of while
	
}//end of strip
