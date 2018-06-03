#include <unistd.h>    
#include <sys/types.h>
#include <stdio.h>     
#include <stdlib.h>   
#include <pthread.h>  
#include <string.h>    
#include <semaphore.h> 

#define THREAD_SIZE 50

/* prototype for thread routine */
void handler ( void *ptr );



sem_t mutex;
int counter; /* shared variable */




int main()
{
    int index[THREAD_SIZE];
   	pthread_t thread[THREAD_SIZE];

    int i = 0;
	/* argument to threads */

	for(i=0; i<THREAD_SIZE; i++)
	{
		index[i] = i+1;
	}



   	 /* initialize mutex here*/




 
	for(i=0; i<THREAD_SIZE; i++)
	{
		pthread_create (&thread[i], NULL, (void *) &handler, (void *) &index[i]);
	}

    	for(i=0; i<THREAD_SIZE; i++)
	{
		pthread_join(thread[i], NULL);
	}


    /* destroy semaphore here*/

    
    exit(0);
}

void handler ( void *ptr )
{
    int x;
    x = *((int *) ptr);
    printf("Thread %d: Waiting to enter critical region...\n", x);


    /* down semaphore here*/


    /* START CRITICAL REGION */
    printf("Thread %d: Now in critical region...\n", x);
    printf("Thread %d: Counter Value: %d\n", x, counter);
    printf("Thread %d: Incrementing Counter...\n", x);
    counter++;
    printf("Thread %d: New Counter Value: %d\n", x, counter);
    printf("Thread %d: Exiting critical region...\n", x);
    /* END CRITICAL REGION */


    /* up semaphore here*/



    pthread_exit(0); /* exit thread */
}
