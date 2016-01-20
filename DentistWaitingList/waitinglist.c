#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char x[6][20];
int counter = 0;
char *p; //make pointer to use in count_letter

void reserve(void);
void cancel(void);
void list(void);
void emergency(void);
int count_letter(char ch);

int main(void)
{
	int option;
	int number;
	char letter;

	while(1)
	{
		//Give users option to input number to choose
		printf("What would you like to do?\n");
		printf("(1) Schedule appointment.\n(2) Cancel appointment.\n");
		printf("(3) See list of appointments.\n(4) Emergency appointment.\n");
		printf("(5) Count a letter.\n(6) Quit with any other key.\n ");
		if(scanf("%d", &option) != 1)  //Read the input option
		{
			printf("Wrong entry.");
			return 0;
		}

		switch(option)
		{
			//Schedule an appointment
			case 1:
			{
				reserve();
				break;
			}

			//Cancel appointment
			case 2:
			{
				cancel();
				break;
			}

			//See list of appointments
			case 3:
			{
				list();
				break;
			}
			//automatically put reservation to top
			case 4:
			{
				emergency();
				break;
			}
			//Count an inputted letter
			case 5:
			{
				printf("Which letter?\n");
				fpurge(stdin); //delete spaces
				scanf("%c", &letter);
				fpurge(stdin);
				number = count_letter(letter);
				printf("%d occurrences of the letter %c.\n", number, letter);
				break;
			}

			//Quit the program
			default:
				return 0;

		}
	}
}

void reserve(void)
{
	int i;
	char id[20];
	if(counter == 6)
	{
		printf("There are no available appointments.\n\n");
		return;
	}

	printf("Enter your name.\n");
	scanf("%s", id); //Read input from user, put earliest open spot in array
	for(i = 0; i<6; i++)
	{
		if(strcmp(id, x[i]) == 0)
		{
			printf("There is already a reservation under that name.\n");
			break;
		}
	}

	if(i==6)
	{
		//Print the inputted name and time
		printf("Your reservation is under %s at %d PM.\n\n", id, counter+1);
		strcpy(x[counter], id); //cut into earlier spot
		counter++; //add to counter
	}
}

void cancel(void)
{
	char name[20];
	int i;
	int j;

	printf("Enter your name to cancel your appointment.\n");
	scanf("%s", name);
	for(i = 0; i<6; i++)
	{
		if(strcmp(name, x[i]) == 0)  //Check if strings are equal to see if input is in array
		{
			//Make the appointment slot empty
			printf("Your reservation has been canceled.\n");
			for(j = i+1; j<6; j++)
			{
				//Move names up by copying into previous element
				strcpy(x[j-1], x[j]);
			}

			x[counter-1][0] = '\0'; //Go to end
			counter--;
			break;
		}
	}

	if(i==6)
	{
		printf("No appointment is reserved under this name.\n");
	}
}

void list(void)
{
	int i;
	if(counter == 0)
	printf("There are currently no appointments scheduled.\n");
	else
	{
		printf("List of current appointments:\n");
		for(i = 0; i<6; i++)
		{
			//Check if there is an item in the array
			if(x[i][0] != '\0')
				printf("%s \n", x[i]);
			if(x[i][0] == '\0')
				printf("Empty.\n");
		}
		printf("\n");
	}
	return;
}


int count_letter(char ch)
{
	int count = 0; //track occurences of ch inputted from letter in main
	int i;
	for(i = 0; i<6; i++)
	{
		p = x[i]; //have pointer go through each spot
		while(*p != '\0') //until the end 
		{
			if(*p == ch) //if the letter is found
				count++;
			p++; //continue through next spot
		}
	}

    return count;
}


void emergency(void)
{
	int i;
	char temp[20]; //use to store last name if applicable
	char id[20];
	printf("Enter your name.\n");
	scanf("%s", id); //Read input from user, put into the first spot of the array
	for(i = 0; i<6; i++)
	{
		if(strcmp(id, x[i]) == 0) //check if name is already reserved
		{
			printf("There is already a reservation under that name.\n");
			return;
		}
	}
	
	if(counter == 6) //check if any name is being overridden
	{
		strcpy(temp, x[5]); //store it into a temp value
		printf("The reservation under %s has been canceled.\n", temp);
	}

	printf("Your emergency reservation is under %s at %d PM.\n", id, 1);
	for(i = 5; i>=0; i--)
		strcpy(x[i], x[i-1]); //move all spots back
	strcpy(x[0], id); //copy new name into first spot
	if(counter != 6)
		counter++;
}




