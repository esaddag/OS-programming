#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>



#define NO_OF_PROCESS 2

#define BUFFER_SIZE 1024

int shortest(int arr[5])
{
	int min=0;
	int i;
	for(i=0;i<5;i++)
	{
		if(arr[i]<min)
			{
				min=arr[i];
				arr[i]=NULL;
			}
	}
}

int main(int argc, char* argv[])
{
	STARTUPINFO si[NO_OF_PROCESS];
	PROCESS_INFORMATION pi[NO_OF_PROCESS];
	HANDLE processHandles[NO_OF_PROCESS];

	char szBuffer[BUFFER_SIZE];
	DWORD cbBytes;

	char* pipeName = "\\\\.\\Pipe\\MyNamedPipe";
	char* lpCommandLine[NO_OF_PROCESS] = { "child.exe 1", "child.exe 2" };
	int i = 0;
	
	int t[5] = { 300,220,180,45,225 };
	HANDLE hPipe;
	
	//creating named pipe
	hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE , 5, BUFFER_SIZE, BUFFER_SIZE, 500, NULL);

	//checking pipe creation
	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("\nError occurred while "
			"creating the pipe: %d", GetLastError());
	}
	else
	{
		printf("\nCreateNamedPipe() was successful.\n");
	}

	
	//checking connection of pipe
	BOOL bClientConnected = ConnectNamedPipe(hPipe, NULL);


	if (FALSE == bClientConnected)
	{
		printf("\nError occurred while connecting"
			" to the client: %d\n", GetLastError());
		CloseHandle(hPipe);

	}
	else
	{
		printf("\nConnectNamedPipe() was successful.");
	}

	for (i = 0; i < NO_OF_PROCESS; i++)
	{
		SecureZeroMemory(&si[i], sizeof(STARTUPINFO));
		si[i].cb = sizeof(STARTUPINFO);
		SecureZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

		if (!CreateProcess(NULL,
			lpCommandLine[i],
			NULL,
			NULL,
			FALSE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si[i],
			&pi[i]))
		{
			printf("unable to create process: %d\n", i);
			system("pause");
			ExitProcess(0);
		}
		else
		{
			processHandles[i] = pi[i].hProcess;
			printf("parent has created process number %d\n", i);
		}


	}

	//WaitForMultipleObjects(NO_OF_PROCESS, processHandles, TRUE, INFINITE);

	
	BOOL Result = ReadFile(
		hPipe,                // handle to pipe 
		szBuffer,             // buffer to receive data 
		sizeof(szBuffer),     // size of buffer 
		&cbBytes,             // number of bytes read 
		NULL);                // not overlapped I/O 

	if ((!Result) || (0 == cbBytes))
	{
		printf("\nError occurred while reading "
			"from the child: %d", GetLastError());
		CloseHandle(hPipe);
		return 1;  //Error
	}
	else
	{
		printf("\nReadFile() was successful.");
	}

	Result = WriteFile(
		hPipe,                // handle to pipe 
		szBuffer,             // buffer to write from 
		strlen(szBuffer) + 1,   // number of bytes to write, include the NULL 
		&cbBytes,             // number of bytes written 
		NULL);                // not overlapped I/O 

	if ((!Result) || (strlen(szBuffer) + 1 != cbBytes))
	{
		printf("\nError occurred while writing"
			" to the client: %d", GetLastError());
		CloseHandle(hPipe);
		return 1;  //Error
	}
	else
	{
		printf("\nWriteFile() was successful.");
	}


	for (i = 0; i < NO_OF_PROCESS; i++)
	{
		CloseHandle(pi[i].hThread);
		CloseHandle(pi[i].hProcess);
		CloseHandle(hPipe);
	}

	//ejectDisk('F');
	system("pause");
	return 1;
}




/*
This method is implemented to eject your CD driver
You can check it out for fun :)
*/
/*BOOL ejectDisk(TCHAR driveLetter)
{
	char* tmp = (char*)malloc(sizeof(char) * 100);


	sprintf_s(tmp, sizeof(tmp) * 10, _T("\\\\.\\%c:"), driveLetter);

	HANDLE handle = CreateFile(tmp, GENERIC_READ, FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (handle == INVALID_HANDLE_VALUE)
	{
		printf("cannot open volume\n");
		system("pause");
		ExitProcess(0);
	}
	DWORD bytes = 0;

	if (!DeviceIoControl(handle, FSCTL_LOCK_VOLUME, 0, 0, 0, 0, &bytes, 0))
	{
		printf("cannot complete io request 1\n");
		system("pause");
		ExitProcess(0);
	}

	if (!DeviceIoControl(handle, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &bytes, 0))
	{
		printf("cannot complete io request 2\n");
		system("pause");
		ExitProcess(0);
	}

	if (!DeviceIoControl(handle, IOCTL_STORAGE_EJECT_MEDIA, 0, 0, 0, 0, &bytes, 0))
	{
		printf("cannot complete io request 3\n");
		system("pause");
		ExitProcess(0);
	}


	CloseHandle(handle);

	return TRUE;
}
*/
//C:\\WINDOWS\\system32\\mspaint.exe