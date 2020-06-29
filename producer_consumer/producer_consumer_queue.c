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

int buffer[BUFFER_SIZE],buffer_front,buffer_rear;

void enqueue(int a)
{
	if (buffer_front == -1)
		buffer_front++;
	buffer_rear = (buffer_rear + 1) % BUFFER_SIZE;
	buffer[buffer_rear] = a;
}

int dequeue()
{
	int temp = buffer[buffer_front];
	if (buffer_front == buffer_rear)
		buffer_front = buffer_rear = -1;
	else
		buffer_front = (buffer_front + 1) % BUFFER_SIZE;
	return temp;
}

void display_queue()
{
	int i=0;
	if(buffer_front==buffer_rear && buffer_front==-1)
	{
		printf("\tempty");
	}
	else
	{
		for(i=buffer_front;;i=(i+1)%BUFFER_SIZE)
		{
			printf("\t%d",buffer[i]);
			if(i==buffer_rear)
				break;
		}
	}
}

void *producer(void *arg)
{
	while(1)
	{
		sleep(10+rand() % 10);
		int k = rand() % 10;
		printf("\n\nProducer %d has produced %d",*((int *)arg),k);
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		enqueue(k);
		printf("\n\nBuffer is: ");
		display_queue();
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		//sleep(rand() % 10);
	}
}

void *consumer(void *arg)
{
	while(1)
	{
		sleep(10+rand() % 10);
		int k=0;
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		k=dequeue();
		printf("\n\nConsumer %d has consumed %d",*((int *)arg),k);
		printf("\n\nBuffer is: ");
		display_queue();
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		//sleep(rand() % 10);
	}
}

int main()
{
	int res,producer_count=0,consumer_count=0,i=0,j=0,*arg=NULL;
	pthread_t producer_thread[MAX_COUNT], consumer_thread[MAX_COUNT];
	void *producer_result, *consumer_result;
	res = sem_init(&empty, 0, BUFFER_SIZE);
	buffer_rear=buffer_front=-1;
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
