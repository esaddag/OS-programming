// Barış DÜBEK - 210201042

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
DWORD WINAPI ReadMarket(LPVOID);
int countSales(const char*, const char*);
 const char* products[4] = { "MILK", "BISCUIT", "CHIPS", "COKE" };
char * getDay(const char *str, const char *p1, const char *p2);
LPWSTR dayNumber;
void WritePipe(char* str);
HANDLE hPipe;
DWORD dwWritten;

struct PARAMS
{
	int i;
};
int _tmain(int argc, _TCHAR* argv[])
{
	dayNumber = argv[0];
	LPWSTR pipeName = LPWSTR(malloc(64));
	wsprintf(pipeName, L"\\\\.\\pipe\\Pipe%s", argv[0]);
	hPipe = CreateFile(pipeName,GENERIC_READ | GENERIC_WRITE,	FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

		

	DWORD dwThreadId, dwThreadParam;
	HANDLE hThread[4];
	// Let try a loop...
	for (int x = 0; x < 4; x++)
	{
		dwThreadParam = x;
		PARAMS* params = new PARAMS;
		params->i = x;

		hThread[x] = CreateThread(
			NULL, // default security attributes
			0, // use default stack size
			ReadMarket, // thread function
			params, // argument to thread function
			0, // use default creation flags
			&dwThreadId); // returns the thread identifier

		// Check the return value for success. If something wrong...
		if (hThread == NULL)
			printf("Thread creation failed with an error: %d.\n", GetLastError());
	
	} // end for loop...
	WaitForMultipleObjects(4, hThread, TRUE, INFINITE);
	CloseHandle(hPipe);
	return 0;
}
void WritePipe(char* str)
{
	WriteFile(hPipe,
		str,
		strlen(str),
		&dwWritten,
		NULL);
}
DWORD WINAPI ReadMarket(LPVOID lpdwThreadParam)
{
	
	HANDLE hFile;
	DWORD dwFileSize,dwRead;
	PARAMS* params = (PARAMS*)lpdwThreadParam;

	int productNum = params->i;
	hFile = CreateFile(L"market.txt", GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	
	dwFileSize = GetFileSize(hFile, NULL);
	LPSTR sBuffer = (char*)malloc(dwFileSize+1);
	if (!ReadFile(hFile, sBuffer, dwFileSize, &dwRead, NULL) && dwRead>0)
	{
		printf("Cannot read the file!");
		return -1;
	}
	sBuffer[dwFileSize] = '\0'; // Add null terminator
	

	char arr[2][20];
	
		sprintf(arr[0], "#START DAY %s#", dayNumber);
		sprintf(arr[1], "#END DAY %s#", dayNumber);
		CloseHandle(hFile); // close file handle
		
		char output[100];
		sprintf(output, "[Child %s] [Thread %d] Number of %s are: %d\n", (char*)dayNumber, productNum, products[productNum], countSales(getDay(sBuffer, arr[0], arr[1]), products[productNum]));
		WritePipe(output);
		return 0;

}
char * getDay(const char *str, const char *p1, const char *p2)
{
	const char *i1 = strstr(str, p1);
	if (i1 != NULL)
	{
		const size_t pl1 = strlen(p1);
		const char *i2 = strstr(i1 + pl1, p2);
		if (p2 != NULL)
		{
			/* Found both markers, extract text. */
			const size_t mlen = i2 - (i1 + pl1);
			char *ret = (char*)malloc(mlen + 1);
			if (ret != NULL)
			{
				memcpy(ret, i1 + pl1, mlen);
				ret[mlen] = '\0';
				return ret;
			}
		}
	}
}
int countSales(const char * dayData, const char *productName)
{
	int count = 0;
	const char *tmp = dayData;
	while (tmp = strstr(tmp, productName))
	{
		count++;
		tmp++;
	}
	return count;
}
