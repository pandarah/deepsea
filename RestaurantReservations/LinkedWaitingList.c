

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE struct node

struct node
{
	char names[20]; //store 1 name per member in node
	int seats; //store 1 table size per member in node
	NODE *next;
};

//global
NODE *head = NULL; //first in list
NODE *tail = NULL; //last in list


void insertRes(void) //make reservation
{
	NODE *p, *temp;
	int size;
	char name[20];


	//add reservation to the bottom of the list
	printf("Please enter a name and the number of guests.\n");

	scanf("%s %d", name, &size); //take name and table size from user

	if(head == NULL) //first in list empty
	{
		p = (NODE *)malloc(sizeof(NODE));
		//adjust size to that of nodes
		p->seats = size;
		strcpy(p->names, name);
		//store size and string name
		head = tail = p;
		//only 1 in list, so tail and head
		p -> next = NULL; //empty last spot
		return;
	}

	else if(head != NULL)
	{
		temp = head; //start at beginning

		while(temp!=NULL) //not empty
		{
			if(strcmp(name, temp->names)==0)
			//does not allow duplicate reservations
			{
				printf("There is already a reservation under that name.\n");
				return;
			}
			temp = temp->next;
		}
		
		p = (NODE *) malloc(sizeof(NODE));
		p->seats = size;
		strcpy(p->names, name);
		tail->next = p;
		//put at end of list
		p->next = NULL;
		tail = p;
		//set tail to after last in list
	}

	printf("A table for %d is reserved under %s.\n", p->seats, p->names);
	//show user what they have inputted
}


void removeRes(void)
{
	int freeTable; //store value of how big a table is from user input
	NODE *p, *q;
	p = q = head;
	char bestGroup[20]; //store the name of the best fitting reservation

	printf("Size of free table: "); //allow user to input size of free table
	scanf("%d", &freeTable);
	
	if(p == NULL) //if empty
	{
		printf("No reservations.\n");
		return;
	}
	while(p!= NULL) //not empty
	{
		if(p->seats <= freeTable) //if the size fits, stop at that spot
			break;
		q = p;
		p = p->next;
	}

	if(p == NULL)
	{
		printf("No reservation fits this table.\n");
		return;
	}
	if(p == head) //first reservation fits
	{
		strcpy(bestGroup, head->names); //store name to display
		head = head->next; //move head over a spot to delete first
	}
	else if(p->next == NULL) //last reservation fits
	{
		strcpy(bestGroup, p->names);
		tail = q; //move tail back
		q->next = NULL; //set last spot empty
	}
	else //reservation in middle fits
	{
		strcpy(bestGroup, p->names);
		q->next = p->next; //move spot up
	}

	printf("%s has been seated.\n\n", bestGroup);
	//display group that was seated
	return;

}


void showList(void) //display reservations
{
	//print the list of reservations from oldest to newest
	NODE *p;
	p = head;

	if(head == NULL) //if array is empty, indicated by counter at 0
		printf("There are currently no reservations.\n\n");
	else
	{
		while(p!=NULL)
		{
			printf("%s \t %d guests\n", p->names, p->seats);
			p = p->next;
	
		}
		printf("\n");
	}
	return;
}


int main()
{
	int option;
	while(1)
	{
		printf("What would you like to do?\n");
		//show user options
		printf("(1)Enter reservation.\n(2)Remove reservation.\n(3)List reservations.\n(4) Quit\n");

		if(scanf("%d", &option)!=1) //read user input to see if valid
		{
			printf("Wrong entry.\n");
			return 0;
		}

		switch(option) //depending on user input, do certain statements
		{
			case 1: //if input is 1 make reservation
				insertRes();
				break;
			case 2:
				removeRes(); //take a reservation of the list
				break;
			case 3:
				showList(); //display list of open reservation slots and current reservations
				break;
			default:
				return 0; //quit

		}
	}
}


