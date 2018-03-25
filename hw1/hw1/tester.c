#include"parser.h"
#include<stdio.h>
#include<string.h>

void printchar(char * test)
{
	while(*test != '\n')
	{
		printf("%c", *test);
		test++;
	}
}

int main()
{
	printf("true = %d\n", 1 == 1);
	printf("false = %d\n", 1 == 0);
	/*char input[] = "Whats his name? jason Brody and owen wilson in: The Darjeeling Limted\n";
	strip(input);
	int size;
	char ** tokens = tokenize(input, &size);
	//printTokenList(tokens, size);
	clearTokenList(tokens, size);
	free(tokens);//*/
	
	FILE * fp = fopen("testfile1", "r");
	char buffer[500];
	char ** tokens;
	int size;
	while(fgets(buffer, 500, fp))
	{
		strip(buffer);
		//printf("%s\n", buffer);
		//printf("Original size: %f", strlen(buffer));
		if(buffer[0] == '\0' || buffer[0] == '\r' || buffer[0] == '\n' || strlen(buffer) <=1)
			continue;
		else
		{//*/
			tokens = tokenize(buffer, &size);
			printf("start printlist \n");
			printTokenList(tokens, size);
			clearTokenList(tokens, size);
			printf("end of clear list\n");
			free(tokens);
		}
		buffer[0] = '\0';
	}//end of while loop
	
	fclose(fp);
	
	return 0;
}//end of main

/*

	while(svtptr_index < original_size && (not_delimit || not_found_start))
	{
		if(checkDelimit(ptr[svtptr_index], delimit, num_delimit))
		{
			if((tolower(ptr[svtptr_index]) == 'a' && tolower(ptr[svtptr_index+1]) == ' '))
			{
				array[index++] = tolower(ptr[svtptr_index]);
			}
			else if (ptr[svtptr_index] == 'i' && ptr[svtptr_index] == '\'' && tolower(ptr[svtptr_index]) == 'm')
			{
				array[index++] = tolower(ptr[svtptr_index++]);
				array[index++] =tolower(ptr[svtptr_index++]);
				array[index++] =tolower(tolower(ptr[svtptr_index]));
			}
			array[index++] = tolower(ptr[svtptr_index]);
			if(index>1)
				not_found_start = 0;
		}
		else
		{
			not_delimit = 0;
		}
		svtptr_index++;
	}
	if(index == 0)
	{
		//printf("index = 0\n");
		return NULL;
	}
	//ptr++;
	
	*/
	
	
	
	/*if(*ptr == 'i' && *(++ptr) == '\'' && *(ptr) == 'm')
			{
				array[index++] = 'i';
				svtptr_index++;
				array[index++] = '\'';
				svtptr_index++;
				array[index++] = 'm';
				svtptr_index++;
			}//end of if*/





/*Word *  quicksort(Word * master)
 {
	if(master == NULL)
		return;
	Word * head = master;
	Word * leftPointer, * leftstart, * rightPointer, * rightstart;
	Word * pivot = master;
	while(head != NULL)
	{
			if(compare(pivot, head) > 0)
			{
				leftstart = head;
				head = head->next;
				leftstart->next = leftPointer;
				leftPointer = leftstart;
			}//end of if statement
			else
			{
				rightstart = head;
				head = head->next;
				rightstart->next = rightPointer;
				rightPointer = rightstart;
			}//end of else statement
			Word * right = quicksort(leftPointer);
			Word * left = quicksort(rightPointer);
			return mergeSortList(left, right);
			//return list;
	}//end of while loop
	
 }//end of quicksort
 
 
 Word * mergeSortList(Word * left, Word * right)
 {
	 Word * listhead, * listtail;
	 if(compare(left, right) > 0)
	 {
		 listhead = left;
		 listtail = listhead;
		 left = left->next;
	 }//end of if
	 else
	 {
		 listhead = right;
		 listtail = listhead;
		 right = right->next;
	 }//end of else
		 
	 while(left != NULL && right != NULL)
	 {
		 if(compare(left, right) > 0)
		 {
			 listtail->next = left;
			 left = left->next;
			 listtail = listtail->next;
		 }
		 else
		 {
			 listtail->next = right;
			 right = right->next;
			 listtail = listtail->next;
		 }
	 }
	 while(right != NULL)
	 {
		 listtail->next = right;
		 listtail = listtail->next;
		 right = right->next;
	 }//end of while right
	 while(left  != NULL)
	 {
		 listtail->next = left;
		 listtail = listtail->next;
		 left = left->next;
	 }//end of while left
	 
	 return listhead;
 }//end of mergsrotedlist*/