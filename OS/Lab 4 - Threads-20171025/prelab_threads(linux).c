#include <stdio.h>
#include <pthread.h>

void *runner(void *param);

int main(int argc,char* argv[])
{
	pthread_t tid;
	pthread_attr_t attr;

	if(argc != 2)
	{
		fprintf(stderr, "We need 2 arguements\n");
		return -1;
	}

	if(atoi(argv[1]) < 0)
	{
		fprintf(stderr, "The arguement must be a positive integer\n");
		return -1;
	}

	//Create your threads here
	
	printf("COUNTDOWN DONE!!!\n");
}

void *runner(void *param)
{
	int i, max = atoi(param);
	
	for(i=1; i<=max; i++)
	{
		printf("Counting: %d\n",i);
		sleep(1);
	}
	
	pthread_exit(0);
}














