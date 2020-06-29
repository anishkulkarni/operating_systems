#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE 20
#define MAX_COUNT 20

sem_t empty, full;

pthread_mutex_t mutex;

int buffer[BUFFER_SIZE],buffer_index;

void *producer(void *arg)
{
	sleep(rand() % 10);
	int k = rand() % 10;
	printf("\n\nProducer %d has produced %d",*((int *)arg),k);
	free(arg);
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	buffer_index++;
	buffer[buffer_index]=k;
	printf("\n\nBuffer is: ");
	if(buffer_index==-1)
		printf("empty");
	for(k=0;k<=buffer_index;k++)
		printf("%d\t",buffer[k]);
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	sleep(rand() % 10);
}

void *consumer(void *arg)
{
	sleep(rand() % 10);
	int k=0;
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	k=buffer[buffer_index];
	buffer_index--;
	printf("\n\nConsumer %d has consumed %d",*((int *)arg),k);
	printf("\n\nBuffer is: ");
	if(buffer_index==-1)
		printf("empty");
	for(k=0;k<=buffer_index;k++)
		printf("%d\t",buffer[k]);
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	sleep(rand() % 10);
}

int main()
{
	int res,producer_count=0,consumer_count=0,i=0,j=0,*arg=NULL;
	pthread_t producer_thread[MAX_COUNT], consumer_thread[MAX_COUNT];
	void *producer_result, *consumer_result;
	res = sem_init(&empty, 0, BUFFER_SIZE);
	buffer_index=-1;
	if (res != 0)
	{
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	res = sem_init(&full, 0, 0);
	if (res != 0)
	{
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	res = pthread_mutex_init(&mutex, NULL);
	if (res != 0)
	{
		perror("Mutex initialization failed");
		exit(EXIT_FAILURE);
	}
	printf("Enter the count of producers: ");
	scanf("%d",&producer_count);
	printf("Enter the count of consumers: ");
	scanf("%d",&consumer_count);
	for(i=0;i<producer_count;i++)
	{
		arg=(int *)malloc(sizeof(int));
		*arg=i+1;
		res = pthread_create(&producer_thread[i], NULL, producer, (void *)arg);
		if (res != 0)
		{
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<consumer_count;i++)
	{
		arg=(int *)malloc(sizeof(int));
		*arg=i+1;
		res = pthread_create(&consumer_thread[i], NULL, consumer, (void *)arg);
		if (res != 0)
		{
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<producer_count;i++)
	{
		res = pthread_join(producer_thread[i],NULL);
		if (res != 0)
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<consumer_count;i++)
	{
		res = pthread_join(consumer_thread[i],NULL);
		if (res != 0)
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);
	printf("\n\n");
	exit(EXIT_SUCCESS);
}
