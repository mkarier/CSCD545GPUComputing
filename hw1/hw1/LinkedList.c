#include"LinkedList.h"


int compare(const void * first, const void * second)
{
	Word * one = (Word *)first;
	Word * two = (Word *)second;
	/*if(strcmp(two->input, one->input) < strcmp(one->input, two->input))
		return 0;
	return 1;//*/
	return strcmp(one->input, two->input);
}//compare


int compareCount(const void * first, const void * second)
{
	Word * one = (Word *)first;
	Word * two = (Word *)second;
	return one->count < two->count;
	//return strcmp(first->input, second->input);
}//compare

/*
This method is to print the list. It calls the objects printWord method;
*/
void printList(Word * list)
{
	printLine();
	printf("|%20s | %9s|\n", "English Word", "count");
	printLine();
	Word * curr = list;
	while(curr != NULL)
	{
		printWord(curr);
		curr = curr->next;
	}//end of while
}//end of list


/*
This method is to clear the link list. Calls a method to clear specific data type.
*/
void clearList(Word ** list)
{
	Word * current = *list;
	Word * next = current->next;
	
	while(next != NULL)
	{
		clearWord(current);
		free(current);
		current = next;
		next = next->next;
	}//end of while
	
	clearWord(current);
	free(current);
}

Word * construct(char * input)
{
	Word *word = (Word *)malloc(sizeof(Word));
	word->input = calloc(strlen(input) +1, sizeof(char));
	memcpy(word->input, input, strlen(input));
	word->count = 1;
	word->next = NULL;
	return word;
}//end of construc


void clearWord(Word * word)
{
	free(word->input);
}

LinkedList * llconstruct()
{
	LinkedList * list = (LinkedList *)calloc(1, sizeof(LinkedList));
	list->head = NULL; //calloc(1, sizeof(Word *));
	list->size = 0;
	return list;
}

void printLine()
{
	printf("|");
	int i = 0;
	for(i = 0; i <=20; i++)
	{
		printf("-");
	}
	printf("|");
	for(i = 0; i<10;i++)
	{
		printf("-");
	}
	printf("|\n");
	
}

void printWord(Word * word)
{
	printLine();
	printf("|%20s |%10d|\n", word->input, word->count);
	printLine();
}

void mergeList(LinkedList ** master, LinkedList ** add)
{
	if(*add == NULL ||(*add)->size == 0)
		return;
	if((*master)->size == 0)
	{
		free(*master);
		*master = *add;
		(*master)->size = (*add)->size;
		return;
	}//end of if statement
	else
	{
		Word * current = (*add)->head;
		while(current != NULL)
		{
			Word * mcur = (*master)->head;
			while(mcur->next != NULL)
			{
				if(strcmp(mcur->input, current->input) == 0)
				{
					mcur->count += current->count;
					break;
				}//end of if
				else
				{
					mcur = mcur->next;
				}
			}//end of while loop
			if(strcmp(mcur->input, current->input) == 0)
			{
				mcur->count += current->count;
			}//end of if
			else
			{
				mcur->next = construct(current->input);
				mcur->next->count = current->count;
				(*master)->size +=1;
			}

			current = current->next;
		}//end of while
		clearList(&(*add)->head);
		//free((*add)->head);
		free(*add);
	}//end of else
}//end of mergeList

