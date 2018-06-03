#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[])
{
	int pid = 0;
	char* message = "";

	if (argc != 2)
	{
		printf("error in child process...now exiting %d\n", argv[0]);
		system("pause");
		exit(0);
	}

	pid = atoi(argv[0]);
	message = argv[1];

	printf("message from parent: %s\n", message, pid);

	system("pause");
	return 1;
}



