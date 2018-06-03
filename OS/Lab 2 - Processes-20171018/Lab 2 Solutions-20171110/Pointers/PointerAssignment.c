#include <stdio.h>

void pointerAssignment()
{
	//define your variables
	int x;
	int *p1, *p2;

	//initialize the int variable, then print its value and address
	x = 0;
	printf("value of x: %d \n", x);
	printf("address of x: %d \n", &x);

	//initialize your pointers and print their values
	p1 = &x;
	p2 = p1;

	printf("p1: %d \n", p1);
	printf("p2: %d \n", p2);
}