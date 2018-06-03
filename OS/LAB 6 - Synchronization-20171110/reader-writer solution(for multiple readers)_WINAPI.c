#include <Windows.h>
#include <stdio.h>

#define MAX_THREADS 20
#define MAX_READERS 15
#define MAX_WRITERS MAXTHREADS-MAX_READERS


void read(int id)
{
	printf("READER %3d: Reading...\n", id);
	Sleep(500);
}

void write(int id)
{
	printf("\tWRITER %3d:  Writing...\n", id);
	Sleep(1000);
}


DWORD WINAPI reader(int id);
DWORD WINAPI writer(int id);

HANDLE fileSem, countSem;

int readerCount = 0;

void main()
{

	HANDLE threads[MAX_THREADS];
	int index;

	//Create semaphores

	//--------------------------------------

	//Create reader and writer threads

	//-------------------------------------


	WaitForMultipleObjects(MAX_THREADS, threads, TRUE, INFINITE);
	CloseHandle(fileSem);
	CloseHandle(countSem);

	system("pause");
	return 1;
}


DWORD WINAPI  reader(int id)
{
	// Solve the critical section problem for readers

}


DWORD WINAPI writer(int id)
{
	// Solve the critical section problem for writers

}
