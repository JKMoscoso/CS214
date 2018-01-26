#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Linked list struct that will hold all the strings, and a pointer to the next node
struct node_ {
    char* string;
    struct node_ * next;
};
typedef struct node_ node;

//Node for the head of the list
node *head = NULL;
//Node for the current focus in the list
node *current = NULL;
//Temporary node that holds the next string to be added to the linked list
node *temp = NULL;


/*
 * sortNodes is a binary insertion sort that sorts
 * the current nodes in the linked list. Words that
 * start with capital letters have precedence and
 * are put before words that start with lowercase
 * letters. This fuction is called each time a new
 * node is added to the linked list.
 */

void sortNodes()
{
	//For Positioning temp through sorting
	node *temp2 = head;
	//For holding the previous node in sorting
	node *prev = head;
	//While loop that traverses the linked list to find the proper place to insert the new string
	while (temp2)
	{
		//Checks for how the new node compares to the focus in the list
		if ((0 < strcmp(temp2->string, temp->string)) && (temp2 == head))
		{
			//temp is greater than the head, make temp the new head
			temp->next = head;
			head = temp;
			break;
		}
		else if (0 < strcmp(temp2->string, temp->string))
		{
			//temp is greater than temp2, place temp between prev and temp2
			prev->next = temp;
			temp->next = temp2;
			break;
		}
		else if (!temp2->next)
		{
			//End of the list, append temp to the end					
			temp2->next = temp;
			break;
		}
		else if (prev == temp2)
		{
			//prev = temp2 = head, increment only temp2
			temp2 = temp2->next;
		}
		else
		{
			//increment both prev and temp2
			prev = prev->next;
			temp2 = temp2->next;
		}
	}
}

/*
 * Simple free function that frees all the nodes in the
 * linked list. This is necessary to prevent memory from 
 * sticking around uselessly. Running valgrind on this
 * program shows that there are no leaks possible.
 */
void freeAll()
{
	//Pointer for holding the next node to be freed
	node * ptrNext = NULL;
	current = head;
	while(current)
	{
		//printf("%s is freed.\n", ptr->string);
		ptrNext = current->next;
		free(current->string);
		free(current);
		current = ptrNext;
	}
	return;
}

/*
 * Main function where the tokenizer is situated. The
 * argument is given in a single string such as 
 * "Sample text" The program first checks if there
 * are any words to sort. If not then the program ends
 * Using isalpha, the string is tokenized and put into
 * individual nodes to be sorted as soon as they are
 * added. The linked list is printed out at the end.
 */
int main(int argc, char **argv)
{
	//Check for 0 inputs, or a single endstring character
	if(argc<2 || argv[1][0] == '\0')
	{
		fprintf(stderr, "Error: No input.\n");
		return 0;
	}
	else if(strcmp(argv[1], "-h") == 0)
	{
		printf("Usage: ./pointersorter \"Enter string here\" \n");
		return 0;
	}
	else if(argc>2)
	{
		printf("Error: More than one argument passed.\n");
		return 0;
	}
	//String to hold the next read in string
	char* nodeString = malloc(1000);
	//Counter to track input string lengths
	int counter = 0;
	

	//Check if the first character of the string given is a alphabetical character
	if(!isalpha(argv[1][0]))
	{
		//If not when scan through the string until it finds one
		for(; counter < strlen(argv[1])-1; counter++)
		{
			if(isalpha(argv[1][counter]))
				break;
		}
	}
	//If if can't find one then give out an error.
	if(counter == strlen(argv[1])-1 && !isalpha(argv[1][0]))
	{
		fprintf(stderr, "Error: No words in given string.\n");
		return -1;
	}

	//For loop that creates the linked list of sorted strings
	for(; counter < strlen(argv[1]); counter++)
	{
		//Counter for the position of the input string in the node string
		int x = 0;
		//Start of the tokenizing.
		while(isalpha(argv[1][counter]))
		{
			nodeString[x] = argv[1][counter];
			counter++;
			x++;
		}
		nodeString[x] = '\0';
		//Put newly tokenized string into a linked list.
		if(head == NULL && nodeString[0] != '\0')
		{
			//If there is no head and there is an input, add the first input as the head
			head = malloc(sizeof(node));
			head->string = malloc(strlen(nodeString));
			head->string = strdup(nodeString);
			current = head;
		}
		else if(nodeString[0] != '\0')
		{
			//There is a head node, and there is another node to be added
			//temp == next node
			//current == current node
			temp = malloc(sizeof(node));
			temp->string = malloc(sizeof(nodeString+1));
			strcpy(temp->string, nodeString);
			//STRING SORTING HAPPENS HERE
			sortNodes();
			
		}
	}
	
	//Print out linked list
	current = head;
	while(current)
	{
		printf("%s\n", current->string);
		current = current->next;
	}	
	
	//Free all malloc calls
	free(nodeString);
	freeAll();
	
	return 0;
}
