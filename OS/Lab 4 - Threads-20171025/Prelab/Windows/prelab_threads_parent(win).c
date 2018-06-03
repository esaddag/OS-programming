#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define NO_OF_PROCESS 1


int main(int argc, char* argv[])
{
	int i = 0, pid=0;
	STARTUPINFO si[NO_OF_PROCESS];
	PROCESS_INFORMATION pi[NO_OF_PROCESS];
	HANDLE handles[NO_OF_PROCESS];
	char* lpCommendLine[NO_OF_PROCESS] = {"demo.exe 4"};


	for(i=0; i<NO_OF_PROCESS; i++)
	{
		SecureZeroMemory(&si[i], sizeof(STARTUPINFO));
		si[i].cb = sizeof(STARTUPINFO);
		SecureZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

		if(!CreateProcess(NULL,
				  lpCommendLine[i],
				  NULL,
				  NULL,
				  FALSE,
				  CREATE_NEW_CONSOLE,
				  NULL,
				  NULL,
				  &si[i],
				  &pi[i]))
		{
			printf("Unable to create process: %s", GetLastError());
			ExitProcess(1);
		}
		else
		{
			handles[i] = pi[i].hProcess;
			printf("parent is working...\n");
		}
	}

	//WaitForMultipleObjects(NO_OF_PROCESS,handles,TRUE,INFINITE);
	WaitForSingleObject(handles[0],INFINITE);
	
	for(i=0; i<NO_OF_PROCESS; i++)
	{
		CloseHandle(pi[i].hProcess);
		CloseHandle(pi[i].hThread);
	}

	
	return 0;
}
