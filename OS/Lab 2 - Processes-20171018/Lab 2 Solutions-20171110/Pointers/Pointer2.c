#include <stdio.h>

int main()
{
	int number = 5;
	char letter = 'e';
	
	int *number_p;
	char *letter_p;
	
	number_p = &number;
	letter_p = &letter;
	
	printf("Address of Number %p\n", number_p);
	printf("Address of Character %p\n\n", letter_p);

	printf("Value of Number %d\n", *number_p);
	printf("Value of Character %c\n\n", *letter_p);

	printf("Address of Number %p\n", (number_p+1));
	printf("Address of Character %p\n", (letter_p+1));
	
	system("pause");
	return 0;
}