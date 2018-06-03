#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>


#define NO_OF_PROCESS 3

BOOL ejectDisk(TCHAR driveLetter);


int main(int argc, char* argv[])
{



	//create necessary parameters here
	//HINT: STARTUPINFO, PROCESS_INFORMATION, lpCommandLine or other parameters if you think they are necessary
	STARTUPINFO  *info;
	int i = 0;



	for (i = 0; i < NO_OF_PROCESS; i++)
	{
		//allocate your memory here	
		//HINT: search for ZeroMemory and SecureZeroMemory() functions from msdn

		

		//create your processes here
		//HINT: search for CreateProcess() function from msdn

	}


	WaitForMultipleObjects(NO_OF_PROCESS, processHandles, TRUE, INFINITE);


	for (i = 0; i < NO_OF_PROCESS; i++)
	{
		//close your handles here
	}


	//ejectDisk('F');
	return 1;
}




//you should not modify this code, it is already working
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

