
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char names[10][20]; //global name array
int seats[10]; //global array to hold size of parties
int counter = 0;
int i, j;

void insertRes(void) //make reservation
{
	int size;
	char name[20];
	if(counter == 10)
	{
		printf("There are no open reservations.\n");
		return;
	}
	//add reservation to the bottom of the list

	printf("Please enter a name and the number of guests.\n");
	scanf("%s %d", name, &size); //take name and table size from user
	
	for(i = 0; i<10; i++)
	{
		if(strcmp(name,names[i])==0) //does not allow duplicate reservations
		{
			printf("There is already a reservation under that name.\n"); 
			break;
		}
	}

	if(i==10) //when array reaches the end
	{
		strcpy(names[counter], name); //put inputted info into the closest spot
		seats[counter] = size; //set the second array to store the size of table in same corresponding spot
		printf("A table for %d is reserved under %s.\n", size, name); //show user what they have inputted
		counter++; //track how many reservations
	}
}

void removeRes(void) //seat a group at open table
{
	int freeTable; //store value of how big a table is from user input
	int i, j, k; //use to traverse loops
	int counter2 = 0;
	int bestFit; //used to find the best fitting group for the table size
	char bestGroup[20]; //store the name of the best fitting reservation
	printf("Size of free table: "); //allow user to input size of free table
	scanf("%d", &freeTable);
	
	for(k = 0; k<counter; k++)
	{
		if(seats[k] <  freeTable || seats[k] == freeTable)
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
		bestFit = seats[i];
		
		for(i = 1; i<=counter; i++)
		{
			if(seats[i] == freeTable || (seats[i] > bestFit && seats[i] < freeTable))
			{
		/* EC: I assigned the variable bestFit to the first first spot in the array holidng
		 the size of the groups. I then traverse the array looking for if an element in the array is less than
 		that spot but still fits in the bounds of the table size, or if it is an exact fit to the table size,
 		and if it is, that value becomes bestFit. */
        	
				
				strcpy(bestGroup, names[i]); //store resrvation name in seperate memory slot
				bestFit = seats[i]; //store the # of guests for that spot in bestFit
				
				for(j = i+1; j<counter+1; j++)
				{
					strcpy(names[j-1], names[j]);
					seats[j-1] = seats[j];
					//move all names below the selected reservation up one spot
				}
			}

		
			names[counter-1][0] = '\0';//make the last spot empty
			counter--; //delete one reservation
			break;
		
		}
		
		printf("%s has been seated.\n", bestGroup);
	}
	
	
}


void showList(void) //display reservations
{
	//print the list of reservations from oldest to newest
	int i;
	if(counter ==0) //if array is empty, indicated by counter at 0
		printf("There are currently no reservations.\n\n");
	else
	{
		printf("Current reservations:\n");
		for(i=0;i<10;i++) //go down each row
		{
			if(names[i][0]!='\0') //if element is not empty, print it
			{
				printf("%s \t %d guests\n", names[i], seats[i]); 
				//display name and guests from seats array in same spot as names
			}
			if(names[i][0]=='\0') //if the name array is empty, state as such
				printf("Open reservation.\n");
		}
		printf("\n");
	}

}

int main()
{
	int option;
	while(1)
	{
		printf("What would you like to do?\n");
		//show user options
		printf("(1)Enter reservation.\n(2)Remove reservation.\n(3)List reservations.\n(4)Quit.\n");

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
