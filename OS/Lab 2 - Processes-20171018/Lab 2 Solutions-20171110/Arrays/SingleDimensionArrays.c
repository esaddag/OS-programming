#include <stdio.h>

// An array is a collection of variables of the same type that are referenced by a common name.
// A specific element in an array is accessed by an index.
// All arrays are placed to continuous memory areas.
// Arrays may have one to several dimensions.

void main()
{
	int x[10]; /* this rezerves 10 integer elements */
	int t;

	//initialize your array
	for (t = 0; t < 10; t++)
	{
		x[t] = t;
	}
	
	//access the elements of your array
	for (t = 0; t < 10; t++)
	{
		printf("x[%d]= %d \n", t, x[t]);
	}

	system("pause");
}