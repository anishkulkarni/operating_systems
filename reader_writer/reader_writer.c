#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE 20
#define MAX_COUNT 20

sem_t wsem,mutex;

int reader_count,data;

//pthread_mutex_t mutex;

void *writer(void *arg)
{
	while(1)
	{
		sleep(10+rand() % 10);
		sem_wait(&wsem);
		data=(rand()%10);
		printf("\nWriter %d has written %d",*((int *)arg),data);
		printf("\nValue of data is now %d",data);
		sem_post(&wsem);
	}
}

void *reader(void *arg)
{
	while(1)
	{		
		sleep(10+rand() % 10);
		sem_wait(&mutex);
		//pthread_mutex_lock(&mutex);
		reader_count++;
		if(reader_count==1)
			sem_wait(&wsem);
		sem_post(&mutex);
		//pthread_mutex_unlock(&mutex);
		printf("\nReader %d has read %d",(*(int *)arg),data);
		printf("\nValue of data is now %d",data);
		sem_wait(&mutex);
		//pthread_mutex_lock(&mutex);
		reader_count--;
		if(reader_count==0)
			sem_post(&wsem);
		sem_post(&mutex);
		//pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	int res,writer_count=0,reader_count=0,i=0,j=0,*arg=NULL;
	pthread_t writer_thread[MAX_COUNT], reader_thread[MAX_COUNT];
	void *writer_result, *reader_result;
	res = sem_init(&wsem, 0, 1);
	if (res != 0)
	{
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	reader_count=0;
	res = sem_init(&mutex,0,1);
	if (res != 0)
	{
		perror("Mutex initialization failed");
		exit(EXIT_FAILURE);
	}
	printf("Enter the count of writers: ");
	scanf("%d",&writer_count);
	printf("Enter the count of readers: ");
	scanf("%d",&reader_count);
	for(i=0;i<writer_count;i++)
	{
		arg=(int *)malloc(sizeof(int));
		*arg=i+1;
		res = pthread_create(&writer_thread[i], NULL, writer, (void *)arg);
		if (res != 0)
		{
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<reader_count;i++)
	{
		arg=(int *)malloc(sizeof(int));
		*arg=i+1;
		res = pthread_create(&reader_thread[i], NULL, reader, (void *)arg);
		if (res != 0)
		{
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<writer_count;i++)
	{
		res = pthread_join(writer_thread[i],NULL);
		if (res != 0)
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<reader_count;i++)
	{
		res = pthread_join(reader_thread[i],NULL);
		if (res != 0)
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	sem_destroy(&wsem);
	//pthread_mutex_destroy(&mutex);
	sem_destroy(&mutex);
	printf("\n\n");
	exit(EXIT_SUCCESS);
}
