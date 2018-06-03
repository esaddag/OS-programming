#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>


typedef struct{
	int start;
	int end;
	int thread;
}THREAD_PARAMETERS;

DWORD WINAPI threadwork(LPVOID param);



int main(int argc, char* argv[])
{
	int thread_count,i;
	HANDLE* handles;
	THREAD_PARAMETERS* param;
	int* threadID;


	if(argc != 2)
	{
		printf("error in child process\n");
		system("pause");
		exit(0);
	}


	thread_count = atoi(argv[1]);
	handles = (HANDLE*)malloc(sizeof(HANDLE) * thread_count);
	param = (THREAD_PARAMETERS*)malloc(sizeof(THREAD_PARAMETERS) * thread_count);
	threadID = (int*)malloc(sizeof(int) * thread_count);


	for(i=0;i<thread_count;i++)
	{
		//Define Your Thread Parameters here
		
		
		
		
		//Create Your threads here
		if (!CreateThread() {




		}) {
			printf("unable to create thread: %d\n", i);
			system("pause");
			ExitThread(0);
		}
		

		

		if(handles[i] == INVALID_HANDLE_VALUE)
		{
			printf("error in child: cannot create thread\n");
			system("pause");
			exit(0);
		}


		printf("%d - thread %d has started working\n", threadID[i], param[i].thread);
	}
	
	WaitForMultipleObjects(thread_count, handles, TRUE, INFINITE);

	for(i=0;i<thread_count;i++)
	{
		CloseHandle(handles[i]);
	}


	free(param);
	free(handles);
	free(threadID);

	system("pause");
	return 1;
}



DWORD WINAPI threadwork(LPVOID param)
{
	int i;
	THREAD_PARAMETERS* parameter = (THREAD_PARAMETERS*)param;

	/*
		DO YOUR THREAD WORKS HERE..
	*/

	system("pause");
	return 1;
}
