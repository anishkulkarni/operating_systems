#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define PHILOSOPHER_COUNT 5

pthread_mutex_t mutex[PHILOSOPHER_COUNT];

void * philosopher_function(void *arg)
{
	int i=(*(int *)arg)-1;
	while(1)
	{
		switch(i)
		{
		case 0:
			printf("\n| Wants to eat  |               |               |               |               |");
			break;
		case 1:
			printf("\n|               |  Wants to eat |               |               |               |");
			break;
		case 2:
			printf("\n|               |               |  Wants to eat |               |               |");
			break;
		case 3:
			printf("\n|               |               |               |  Wants to eat |               |");
			break;
		case 4:
			printf("\n|               |               |               |               | Wants to eat  |");
			break;
		}
		printf("\n+---------------+---------------+---------------+---------------+---------------+");
		if(i%2==0)
		{
			pthread_mutex_lock(&mutex[i]);
			pthread_mutex_lock(&mutex[(i+1)%5]);
		}
		else
		{
			pthread_mutex_lock(&mutex[(i+1)%5]);
			pthread_mutex_lock(&mutex[i]);
		}
		switch(i)
		{
		case 0:
			printf("\n|Started eating |               |               |               |               |");
			break;
		case 1:
			printf("\n|               |Started eating |               |               |               |");
			break;
		case 2:
			printf("\n|               |               |Started eating |               |               |");
			break;
		case 3:
			printf("\n|               |               |               |Started eating |               |");
			break;
		case 4:
			printf("\n|               |               |               |               |Started eating |");
			break;
		}
		printf("\n+---------------+---------------+---------------+---------------+---------------+");
		sleep(rand()%10);
		pthread_mutex_unlock(&mutex[i]);
		pthread_mutex_unlock(&mutex[(i+1)%5]);
		switch(i)
		{
		case 0:
			printf("\n|Finished eating|               |               |               |               |");
			break;
		case 1:
			printf("\n|               |Finished eating|               |               |               |");
			break;
		case 2:
			printf("\n|               |               |Finished eating|               |               |");
			break;
		case 3:
			printf("\n|               |               |               |Finished eating|               |");
			break;
		case 4:
			printf("\n|               |               |               |               |Finished eating|");
			break;
		}
		printf("\n+---------------+---------------+---------------+---------------+---------------+");
		switch(i)
		{
		case 0:
			printf("\n|Start thinking |               |               |               |               |");
			break;
		case 1:
			printf("\n|               |Start thinking |               |               |               |");
			break;
		case 2:
			printf("\n|               |               |Start thinking |               |               |");
			break;
		case 3:
			printf("\n|               |               |               |Start thinking |               |");
			break;
		case 4:
			printf("\n|               |               |               |               |Start thinking |");
			break;
		}
		printf("\n+---------------+---------------+---------------+---------------+---------------+");
	}
}

int main()
{
	int *arg=NULL,res,i=0;
	pthread_t philosopher[PHILOSOPHER_COUNT];
	void *result;
	for(i=0;i<PHILOSOPHER_COUNT;i++)
		res = pthread_mutex_init(&mutex[i], NULL);
	printf("\n+---------------+---------------+---------------+---------------+---------------+");
	printf("\n| Philosopher 1 | Philosopher 2 | Philosopher 3 | Philosopher 4 | Philosopher 5 |");
	printf("\n+---------------+---------------+---------------+---------------+---------------+");
	for(i=0;i<PHILOSOPHER_COUNT;i++)
	{
		arg=(int *)malloc(sizeof(int));
		*arg=i+1;
		res = pthread_create(&philosopher[i], NULL, philosopher_function, (void *)arg);
		if (res != 0)
		{
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<PHILOSOPHER_COUNT;i++)
	{
		res = pthread_join(philosopher[i],NULL);
		if (res != 0)
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<PHILOSOPHER_COUNT;i++)
		pthread_mutex_destroy(&mutex[i]);
	printf("\n\n");
	exit(EXIT_SUCCESS);
}
