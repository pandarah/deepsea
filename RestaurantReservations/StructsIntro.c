
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//create union to hold age-dependent value
typedef union{
	char school[20];
	float salary;
	int retirement;
} UNION_T;

//struct to hold related info
struct info{
	char name[20];
	int age;
	UNION_T u; //union as a member of struct
};

//global variables
int counter = 0;
struct info x[10]; //array of 10 elements with each member

//functions
void inputPerson(void){
	int tempAge; //take input of age
	char tempName[20]; //take input of name
	struct info *p =x; //point to struct
	int i;

	if(counter==10) //if the list is full
	{
		printf("The list of people is full.\n");
		return;
	}

	printf("What is the person's name and age?\n");
	scanf("%s%d", tempName, &tempAge); //read the name and age

	for(i=0; i<10;i++,p++) //traverse array with pointer
	{
		if(strcmp(tempName, p->name)==0) //if that name is already in the list
		{
			printf("This name is already listed.\n");
			return;
		}
	}

	if(i==10) //if name has not been entered yet
	{
		strcpy(x[counter].name, tempName); //put name into next open spot in struct
		x[counter].age = tempAge; //assign the age member
	}

	//use if statements to pick union member being used depending on age
	if(tempAge <= 21)
	{
		printf("What is the person's school?\n");
		scanf("%s", x[counter].u.school); //assign school as status string
	}
	else if(tempAge > 21 && tempAge < 65)
	{
		printf("What is the person's monthly salary?\n");
		scanf("%f", &x[counter].u.salary); //status is salary float
	}
	else if(tempAge >= 65)
	{
		printf("How many years has this person been retired?\n");
		scanf("%d", &x[counter].u.retirement); //status is years retired int
	}

	counter++;

}


void removePerson(void){
	char tempName[20];
	int i;

	printf("Which person should be removed?\n");
	scanf("%s", tempName);
	
	for(i = 0; i<= counter; i++)
	{
		if(strcmp(x[i].name, tempName) == 0) //if the name is found
		{
			strcpy(x[i].name, x[counter-1].name);
			//copy last information in struct over info being removed
			x[i].age = x[counter-1].age;
			//copy last age over removed age

			//if statements to select which union is assigned
			if(x[counter-1].age <= 21)
			{
				strcpy(x[i].u.school, x[counter-1].u.school); //move string up
			}
			else if(x[counter-1].age > 21 && x[counter-1].age < 65)
			{
				x[i].u.salary = x[counter-1].u.salary; //move float up
			}
			else if(x[counter-1].age >= 65)
			{
				x[i].u.retirement = x[i].u.retirement; //move int up
			}
			break;

		}
		if(i == counter) //if the name is not found
		{
			printf("Person not found in the list.\n");
			return;
		}

	}
	counter--;
}

void listPeople(){
	int i;
	struct info *p = x; //traverse array with string

	if(counter == 0) //array is empty
	{
		printf("There are no people listed.\n");
	}
	else
	{
		for(i=0;i<counter;i++, p++)
		{
			printf("Person %d:\n", i+1);
	
			//print different information depending on age
			if(p->age <= 21)
			{
				printf("Name: %s\tAge: %d\t Status: %s\n", p->name, p->age, p->u.school);
				 //status is string school
			}
			else if(p->age > 21 && p->age < 65)
			{
				printf("Name: %s\tAge: %d\t Status: $%.2f\n", p->name, p->age, p->u.salary);
				 //status is float salary
			}
			else if(p->age >= 65)
			{
				printf("Name: %s\tAge: %d\t Status: %d years\n", p->name, p->age, p->u.retirement);
				 //status is years retired int
			}
		}
		printf("\n\n");
	}
}


int main()
{
	int option;
	
	while(1)
	{
		printf("What would you like to do?\n");
		printf("(1)Input a person.\n(2)Remove a person.\n(3)List people.\n(4)Quit.\n");

		if(scanf("%d", &option)!=1)
		{
			printf("Wrong entry.\n");
			return 0;
		}

		switch(option)
		{
			case 1:
				inputPerson(); //insert name
				break;
			case 2:
				removePerson(); //copy last element in array to index being removed
				break;
			case 3:
				listPeople(); //display all people in list
				break;
			default:
				return 0; //quit
		}
	
	}
}

