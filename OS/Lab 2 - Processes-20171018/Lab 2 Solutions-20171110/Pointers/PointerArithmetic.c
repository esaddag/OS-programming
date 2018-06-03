#include <stdio.h>

void pointerArithmetic()
{
	int *count_ptr;
	int count = 0; // initialize your count variable

	count_ptr = &count; //initialize your pointer

	//Incrementing the value of count by using the pointer
	while (count < 10)
	{
		(*count_ptr)++; //increment the value
		printf("current value of count: %d \n", count);
	}

	//Incrementing your pointer
	printf("current address that the pointer shows: %d \n", count_ptr);
	count_ptr++;
	printf("updated address of the pointer: %d \n", count_ptr); //Notice that the address does not increment by 1, the increment varies according to the size of pointer type.
}
