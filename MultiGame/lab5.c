
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	srand((int)time(NULL));

	int perc=0;
	int i;

	
	printf("Solve these 10 multiplication problems.\n");
	//Loop to show 10 multiplication problems
	for(i=0; i<10; i++)
	{
		int a = rand() % 13;
		int b = rand() % 13;
		int response;
		//Show the numbers being multiplied
		printf("%d * %d is \n", a, b);
		//Stops the program if the user inputs something other than an integer
		if(scanf("%d", &response) != 1)
		{
			printf("Wrong entry. \n");
			return 0;
		}
		/*If the user's input is the correct, add to the percentage variable
		 and tell the user they are correct*/
		if(response == a*b)
		{
			printf("Correct!\n");
			perc += 10;
		}
		else
			printf("Incorrect. \n");
	}

	//Display the percentage correct and return to end the program
	printf("You got %d%% correct! \n", perc);
	return 0;
}
