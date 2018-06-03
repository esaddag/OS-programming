#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


#define BUFFSIZE 1024 
int sjf(int actual, int estimated)
{
	return ((actual / 2) + (estimated / 2));
}

int main(int argc, char* argv[])
{
	char* pipeName = " \\\\.\\Pipe\\MyNamedPipe";
	int pid = 0;
	char* message = "";
	HANDLE hPipe;
	CHAR Buf[BUFSIZE];
	DWORD dwRead, dwWritten;
	HANDLE hStdin, hStdout;
	BOOL Success;


	if (argc != 2)
	{
		printf("error in child process...now exiting %d\n",argv[0]);
		system("pause");
		exit(0);
	}

	pid = atoi(argv[0]);
	message = argv[1];

	printf("message from parent: %s\n", message);
	
	hPipe = CreateFile(
		pipeName,   // pipe name 
		GENERIC_READ |  // read and write access 
		GENERIC_WRITE,
		0,              // no sharing 
		NULL,           // default security attributes
		OPEN_EXISTING,  // opens existing pipe 
		0,              // default attributes 
		NULL);

	if (hPipe == INVALID_HANDLE_VALUE)
		printf("process %s cannot connected\n", message);

	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("\nError occurred while connecting"
			" to the server: %d", GetLastError());

		//WaitNamedPipe(hPipe, NMPWAIT_WAIT_FOREVER);
		//One might want to check whether the server pipe is busy
		//This sample will error out if the server pipe is busy
		//Read on ERROR_PIPE_BUSY and WaitNamedPipe() for that
		WaitNamedPipe(pipeName, NMPWAIT_WAIT_FOREVER);
		printf("\nError occurred while waiting the pipe: %d", GetLastError());
		 //Error
	}
	else
	{
		printf("\nCreateFile() was successful.");
	}

	CHAR Buf[BUFSIZE];
	DWORD dwRead, dwWritten;
	HANDLE hStdin, hStdout;
	BOOL Success;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (
		(hStdout == INVALID_HANDLE_VALUE) ||
		(hStdin == INVALID_HANDLE_VALUE)
		)
		ExitProcess(1);

	// Send something to this process's stdout using printf.
	printf("\n ** This is a message from the child process. ** \n");

	// This simple algorithm uses the existence of the pipes to control execution.
	// It relies on the pipe buffers to ensure that no data is lost.
	// Larger applications would use more advanced process control.

	while(1)
	{
		// Read from standard input and stop on error or no data.
		Success = ReadFile(hStdin, Buf, BUFSIZE, &dwRead, NULL);

		if (!Success || dwRead == 0)
			break;

		// Write to standard output and stop on error.
		Success = WriteFile(hStdout, Buf, dwRead, &dwWritten, NULL);

		if (!Success)
			break;
	}
	return 0;

	system("pause");
	return 1;
}




