// Barış DÜBEK- 210201042

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
struct PARAMS
{
	int i;
};
DWORD WINAPI CreatePipe(int);
void CreateChild(int childNumber)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	LPWSTR childNum = LPWSTR(malloc(16));
	wsprintf(childNum, L"%d", childNumber);
	if (!CreateProcess(L"child.exe", childNum, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		printf("Child process cannot be created..");
	}
}
DWORD WINAPI CreatePipe(LPVOID lpParameter)
{
	char buffer[1024];
	DWORD dwRead;
	HANDLE hPipe;
	PARAMS* params = (PARAMS*)lpParameter;

	int pipeNumber = params->i;

	LPWSTR pipeName = LPWSTR(malloc(64));
	wsprintf(pipeName, L"\\\\.\\pipe\\Pipe%d", pipeNumber);
	hPipe = CreateNamedPipe(pipeName,
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
		PIPE_WAIT,
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	CreateChild(pipeNumber);
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer)-1, &dwRead, NULL) != FALSE)
			{
				/* add terminating zero */
				buffer[dwRead] = '\0';

				/* do something with data in buffer */
				printf("%s", buffer);
			}
		}

		DisconnectNamedPipe(hPipe);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	DWORD dwThreadId, dwThreadParam;
	HANDLE hThread[4];
	// Let try a loop...
	for (int x = 1; x <= 7; x++)
	{
		dwThreadParam = x;
		PARAMS* params = new PARAMS;
		params->i = x;

		hThread[x] = CreateThread(
			NULL, // default security attributes
			0, // use default stack size
			CreatePipe, // thread function
			params, // argument to thread function
			0, // use default creation flags
			&dwThreadId); // returns the thread identifier

		// Check the return value for success. If something wrong...
		if (hThread == NULL)
			printf("Thread creation failed with an error: %d.\n", GetLastError());

	} // end for loop...
	WaitForMultipleObjects(7, hThread, TRUE, INFINITE);
	system("pause");
	return 0;
}

