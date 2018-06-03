#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>




typedef struct
{
	int start;
	int end;
	int threadNo;
	int* sum;
}THREAD_PARAMETERS;

DWORD WINAPI threadWork(LPVOID parameters);


int main(int argc, char* argv[])
{
	HANDLE* handles;
	THREAD_PARAMETERS* lpParameter;
	int* threadID;
	int i = 0;
	int threadCount = 0;
	int totalsum = 0;


	//check arguments for error
	if (argc != 2)
	{
		printf("error in child process...now exiting %d\n", argv[0]);
		system("pause");
		exit(0);
	}


	//read thread count from arguments
	threadCount = atoi(argv[1]);


	//allocate memory for every parameters needed
	handles = malloc(sizeof(HANDLE)* threadCount);
	lpParameter = malloc(sizeof(THREAD_PARAMETERS)* threadCount);
	threadID = malloc(sizeof(int)* threadCount);



	//for each thread
	for (i = 0; i < threadCount; i++)
	{
		//initialize parameters
		lpParameter[i].start = 0;
		lpParameter[i].end = 8;
		lpParameter[i].threadNo = i + 1;


		handles[i] = CreateThread(NULL, 0, threadWork, &lpParameter[i], 0, &threadID[i]);


		//check errors in creation
		if (handles[i] == INVALID_HANDLE_VALUE)
		{
			printf("error when creating thread\n");
			system("pause");
			exit(0);
		}

		printf("thread %d has started working with id: %d\n", i+1, threadID[i]);

	}


	WaitForMultipleObjects(threadCount, handles, TRUE, INFINITE);


	for (i = 0; i < threadCount; i++)
	{
		totalsum = totalsum + (int)lpParameter[i].sum;
		CloseHandle(handles[i]);
	}

	printf("total sum: %d\n", totalsum);


	free(handles);
	free(lpParameter);
	free(threadID);


	system("pause");
	return 1;
}








DWORD WINAPI threadWork(LPVOID parameters)
{
	THREAD_PARAMETERS* param = (THREAD_PARAMETERS*)parameters;

	int i = 0;
	int sum = 0;

	for (i = param->start; i < param->end; i++)
	{
		sum = sum + i;
		Sleep(1000);
		printf("thread %d is counting: %d\n", param->threadNo, sum);
	}

	param->sum = sum;

	system("pause");
	return 1;
}


