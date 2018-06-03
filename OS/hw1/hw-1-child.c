#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{	int *item_number
	int threadNo;
}THREAD_PARAMETERS;

DWORD WINAPI threadWork(LPVOID parameters);

int main(int argc, char* argv[])
{
	int pid = 0;
	char* message = "";
	HANDLE* handles;
	int threadCount = 4;
	THREAD_PARAMETERS* lpParameter;
	int* threadID;
	int i = 0;
	int process_number = atoi(argv[0]);
	if (argc != 2)
	{
		printf("error in child process...now exiting %d\n", argv[0]);
		system("pause");
		exit(0);
	}

	pid = atoi(argv[0]);
	message = argv[1];

	//allocate memory for every thread parameters needed
	handles = malloc(sizeof(HANDLE)* threadCount);
	lpParameter = malloc(sizeof(THREAD_PARAMETERS)* threadCount);
	threadID = malloc(sizeof(int)* threadCount);

	//for each thread
	for (i = 0; i < threadCount; i++)
	{
		//initialize parameters
		lpParameter[i].threadNo = i + 1;

		handles[i] = CreateThread(NULL, 0, threadWork, &lpParameter[i], 0, &threadID[i]);


		//check errors in creation
		if (handles[i] == INVALID_HANDLE_VALUE)
		{
			printf("error when creating thread\n");
			system("pause");
			exit(0);
		}

		//printf("thread %d has started working with id: %d\n", i + 1, threadID[i]);

	}

	WaitForMultipleObjects(threadCount, handles, TRUE, INFINITE);


	for (i = 0; i < threadCount; i++)
	{	

		//totalsum = totalsum + (int)lpParameter[i].sum;
		CloseHandle(handles[i]);
	}

	printf("total milk: %d\n", (int)lpParameter[2].item_number);


	free(handles);
	free(lpParameter);
	free(threadID);


	//printf("message from parent: %s\n", message, pid);

	system("pause");
	return 1;
}




DWORD WINAPI threadWork(LPVOID parameters)
{
	THREAD_PARAMETERS* param = (THREAD_PARAMETERS*)parameters;

	//int i = 0;
	int sum = 0;


	FILE *ptr_file;
	int x=(param->threadNo)+1;
	char buf[100];

	 fopen_s(&ptr_file ,"market.txt", "r");
	//int i = 1;
	if (!ptr_file)
		return 1;
	char item_name[10];
	int item_counter=0;

	//checking which item to count
	if (x = 0)
	{
		strncpy_s(item_name,4,"MILK",7);
	}else if (x = 1)
	{
		strncpy_s(item_name, 4, "BISCUIT", 7);
	}
	else if (x = 2)
	{
		strncpy_s(item_name, 4, "CHIPS", 7);
	}else if (x = 3)
	{
		strncpy_s(item_name, 4, "COKE", 7);
	}

	//count the item
	while (fgets(buf, 100, ptr_file) != NULL)
	{
		if (strstr(buf, item_name) != NULL)
		{
			item_counter++;
		}
	}
	/*for (i = param->start; i < param->end; i++)
	{
		sum = sum + i;
		Sleep(1000);
		printf("thread %d is counting: %d\n", param->threadNo, sum);
	}

	param->sum = sum;*/
	
	printf("%d %s", item_counter, item_name);
	param->item_number=item_counter;

	system("pause");
	return 1;
}
