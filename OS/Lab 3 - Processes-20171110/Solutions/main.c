#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>


#define NO_OF_PROCESS 3

BOOL ejectDisk(TCHAR driveLetter);

int main(int argc, char* argv[])
{
	STARTUPINFO si[NO_OF_PROCESS];
	PROCESS_INFORMATION pi[NO_OF_PROCESS];
	HANDLE processHandles[NO_OF_PROCESS];

	char* lpCommandLine[NO_OF_PROCESS] = { "demo.exe 1", "demo.exe 2", "demo.exe 3" };
	int i = 0;



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

	WaitForMultipleObjects(NO_OF_PROCESS, processHandles, TRUE, INFINITE);


	for (i = 0; i < NO_OF_PROCESS; i++)
	{
		CloseHandle(pi[i].hThread);
		CloseHandle(pi[i].hProcess);
	}

	ejectDisk('F');
	return 1;
}




/*
This method is implemented to eject your CD driver
You can check it out for fun :)
*/
BOOL ejectDisk(TCHAR driveLetter)
{
	char* tmp = (char*)malloc(sizeof(char)* 100);


	sprintf_s(tmp, sizeof(tmp)*10,  _T("\\\\.\\%c:"), driveLetter);

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

//C:\\WINDOWS\\system32\\mspaint.exe