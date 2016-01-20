
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int division(int x, int y) //declare new function at top or prototype above main
{
	int userAns; //will store users answer
	int dividend = x*y; //find second value to show user

	printf("%d / %d\n", dividend, x); //display 2 numbers being divided
	scanf("%d", &userAns); //store user's answer
	if(userAns != y) //user is wrong
	{
		return 0;
	}
	else //user is right
	{
	return 1;
	}
}

int main()
{
	printf("Division Game\n");
	int counter = 0; //track number of correct answers
	int i; //use for for-loop
	srand((int)time(NULL)); //ensure random values
	for(i = 0; i<10; i++) //run code 10 times
	{
		int divisor = rand() %12 + 1; //divisor will be between 1 and 12
		int quotient = rand() %13; //quotient between 0 and 12
		int ans = division(divisor, quotient);
	 	//run division function, store output in ans
		if(ans == 0) //if output of division is 1
		{
			printf("Wrong!\nThe correct answer was %d.\n", quotient);
		}
		else
		{
			printf("Correct!\n");
			counter++; //add to number of correct answers
		}
	}
	printf("You got %d out of 10 correct.\n", counter); //output counter
}
