#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int total = 0;

typedef struct
{
	int start;
	int end;
	int threadNo;
}THREAD_PARAMETERS;

void *runner(void *param);

int main(int argc, char* argv[])
{
	
	int threadCount = 30;
	pthread_t tid[threadCount];
	pthread_attr_t attr[threadCount];
	
	THREAD_PARAMETERS* lpParameter;
	
	
	lpParameter = malloc(sizeof(THREAD_PARAMETERS)* threadCount);

 	int  i=0;
	
	for(i=0; i<threadCount; i++)
	{
		lpParameter[i].start = 0;
		lpParameter[i].end = 10;
		lpParameter[i].threadNo = i + 1;

		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i],&attr[i],runner,&lpParameter[i]);	
	}

	for(i=0; i<threadCount; i++)
	{
		pthread_join(tid[i],NULL);
	}
	

	printf("Total: %d\n",total);
	return 1;
}

void *runner(void *parameters)
{
	THREAD_PARAMETERS* param = (THREAD_PARAMETERS*)parameters;
	int i = 0;

	for (i = param->start; i < param->end; i++)
	{
		total = total + 1;
		printf("thread %d has made: %d\n", param->threadNo, total);
	}
	
	pthread_exit(0);
}
