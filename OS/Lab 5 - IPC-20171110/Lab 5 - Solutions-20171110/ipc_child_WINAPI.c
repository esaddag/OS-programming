#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

int main()
{
	char message[100];
	int i = 0;


	while (1)
	{

		for (i = 0; (message[i] = getchar()) != 0; i++)
		{
		}

		printf("message from parent process: %s\n", message);

	}


	system("pause");
	return 1;
}