#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>

int main()
{
	char* shared_memory;
	int segment_id;

	const int size = 4096;

	segment_id = shmget(IPC_PRIVATE, size, S_IWUSR | S_IRUSR);

	//Allocate your memory here


	char msg[100];
	int control;
	printf("\n1 to Write, 2 to Read: ");
	scanf("%d",&control);
	while(1)
	{
		if(control ==1)
		{
			//Write your message here
		}
		else if(control == 2)
		{
			//Read your message from here
		}
		else
		{
			break;
		}
	}

	//Destroy your shared memory

	shmctl(segment_id, IPC_RMID ,NULL);
	
	return 0;
}
