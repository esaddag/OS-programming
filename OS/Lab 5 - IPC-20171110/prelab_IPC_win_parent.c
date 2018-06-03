	#include <Windows.h>
#include <stdio.h>

int main()
{
	char message[100];

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sa;

	DWORD bytesToWrite, bytesWritten; //A DWORD is a 32-bit unsigned integer

	HANDLE hWritePipe, hReadPipe;

	//creating security attributes
	SecureZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	//Create your pipe here
	
	SecureZeroMemory(&si, sizeof(STARTUPINFO));
	SecureZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	si.cb = sizeof(si);
	
	//Initialize your Pipe handles here
	

	if(!CreateProcess(NULL,
					  "demo.exe",
					  NULL,
					  NULL,
					  TRUE,
					  CREATE_NEW_CONSOLE,
					  NULL,
					  NULL,
					  &si,
					  &pi))
	{
		printf("unable to create process\n");
		system("pause");
		exit(1);
	}
	

	while(1)
	{
		gets(message);
		bytesToWrite = strlen(message);
		bytesToWrite++;
		
		//Send your message here
		
		printf("numberof bytes: %d\n number of bytes succesfully sent: %d\n", bytesToWrite, bytesWritten);
	}


	system("pause");
	return 0;
}