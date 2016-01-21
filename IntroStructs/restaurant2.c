
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info
{
//structure to hold related items
char names[20]; //store 1 name per member in info
int seats; //store 1 table size per member in info
};

struct info x[10]; //initialize a global structure to hold 10 members
int counter = 0; //global counter

void insertRes(void) //make reservation
{
	int size; //user input number of guests
	int i;
	struct info *p = x; //pointer to structure
	char name[20];

	if(counter == 10)
	{
		printf("There are no open reservations.\n");
		return;
	}
	//add reservation to the bottom of the list

	printf("Please enter a name and the number of guests.\n");
	scanf("%s %d", name, &size); //take name and table size from user

	for(i = 0; i<10; i++, p++)
	{
		if(strcmp(name, p->names)==0) //does not allow duplicate reservations
		{
			printf("There is already a reservation under that name.\n");
			return;
		}
	}

	if(i==10) //when array reaches the end
	{
		strcpy(x[counter].names, name); //put inputted info into the earliest open member
		x[counter].seats = size; //set the int member to the size of the table
		printf("A table for %d is reserved under %s.\n", size, name); //show user what they have inputted
		counter++; //track how many reservations
	}
}

void removeRes(void)
{
	int freeTable; //store value of how big a table is from user input
	int i, j, k; //use to traverse loops
	struct info *p =x; //pointer to structure
	struct info *q; //second pointer
	int counter2 = 0; //track if there are any members that fit into size limitations
	int bestFit; //used to find the best fitting group for the table size
	char bestGroup[20]; //store the name of the best fitting reservation

	printf("Size of free table: "); //allow user to input size of free table
	scanf("%d", &freeTable);

	for(k = 0; k<counter; k++, p++)
	{
		//traverse with pointer, comparing the seats member to inputed value
		if(p->seats <  freeTable || p->seats == freeTable)
		{
			counter2++;
		}
	}

	if(counter2 == 0)
	{
		printf("No reservation fits this table.\n");
		return;
	}

	else if(counter2 != 0)
	{
		p=x; //reset pointer to the beginning of the structure memory
		bestFit = 0;

		for(i = 0; i<counter; i++, p++)
		{
			if(p->seats == freeTable || (p->seats > bestFit && p->seats < freeTable))
			//traverse with pointer through all seat members of the structure
			{
				if(p->seats == bestFit)
					continue; //continue to remove the earliest reservation that fits
				
				strcpy(bestGroup, p->names); //store reservation name in separate memory slot
				bestFit = p->seats; //store the # of guests for that member in bestFit
				//set second pointer to spot where p ends
				q=p;

			}	

		}

		for(j = 0; j<counter-1; j++,q++)
		{
			//move all reservations up one after deleting by shifting members up
			strcpy(q->names, (q+1)->names);
			q->seats= (q+1)->seats;
		}

	x[counter-1].names[0] = '\0';//make the last member empty
	x[counter-1].seats = 0;
	counter--; //delete one reservation
	printf("%s has been seated.\n", bestGroup);
	return;
	}
}


void showList(void) //display reservations
{
	//print the list of reservations from oldest to newest
	int i;
	struct info *p = x;
	
	if(counter ==0) //if array is empty, indicated by counter at 0
		printf("There are currently no reservations.\n\n");
	else
	{
		printf("Current reservations:\n");
		for(i=0;i<10;i++, p++) //go down each row
		{
			if(p->names!='\0' && p->seats!= 0) //if element is not empty, print it
			{
				printf("%s \t %d guests\n", x[i].names, x[i].seats);
				//display name and guests from seats array in same spot as names
			}
			
			if(p->names=='\0' || p->seats == 0) //if the name array is empty, state as such
			printf("Open reservation.\n");
		}
		printf("\n");
	}

}

void search_size(void){
	int size;
	int i;
	int counter2 = 0;
	struct info *p = x;

	printf("What is the size of the table?\n");
	scanf("%d", &size);
	printf("Groups waiting for this size:\n");
	for(i=0;i<counter;i++,p++)
	{
		if(size == p->seats)
		{
			printf("%s\n", p->names);
			counter2++;
		}
	}
	if(counter2==0)
	printf("None\n");

	return;
}

int main()
{
	int option;
	while(1)
	{
		printf("What would you like to do?\n");
		//show user options
		printf("(1)Enter reservation.\n(2)Remove reservation.\n(3)List reservations.\n(4)Search size.\n(5) Quit\n");

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
			case 4:
				search_size();
				break;
			default:
				return 0; //quit
		}
	}
}

