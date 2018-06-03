#include <stdio.h>
#include <windows.h>



int main(int argc, char* argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sa;
	HANDLE writePipe, readPipe;
	char message[100];
	int bytesToWrite = 0;
	int bytesWritten = 0;


	//creating security attributes
	SecureZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);


	//creating the pipe
	if (!CreatePipe(&readPipe, &writePipe, &sa, 0)) //use the default buffer size.
	{
		printf("unable to create pipe\n");
		system("pause");
		exit(0);
	}


	//creating variables for child process
	SecureZeroMemory(&si, sizeof(STARTUPINFO));
	SecureZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	si.cb = sizeof(STARTUPINFO);
	si.hStdInput = readPipe;
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si.dwFlags = STARTF_USESTDHANDLES;



	//create child process
	if (!CreateProcess(NULL, "demo.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		printf("cannot create child process\n");
		system("pause");
		exit(0);
	}


	//send messages through pipe
	while (1)
	{
		gets_s(message, 100);
		bytesToWrite = strlen(message);
		bytesToWrite++;

		//check errors 
		// WriteFile function writes data to the specified file or input / output(I / O) device.
		if (!WriteFile(writePipe, message, bytesToWrite, &bytesWritten, NULL))
		{
			printf("unable to write to pipe\n");
			system("pause");
			exit(0);
		}

		printf("number of bytes: %d  --  number of bytes sent: %d\n", bytesToWrite, bytesWritten);
	}



	free(&si);
	free(&pi);
	free(&sa);
	CloseHandle(readPipe);
	CloseHandle(writePipe);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	system("pause");
	return 1;
}

