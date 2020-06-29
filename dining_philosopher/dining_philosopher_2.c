#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define PHILOSOPHER_COUNT 5
#define LEFT(x) (x + 4) % 5
#define RIGHT(x) (x + 1) % 5 

enum s {THINKING,HUNGRY,EATING};

enum s state[PHILOSOPHER_COUNT];

pthread_mutex_t mutex, philosopher_semaphore[PHILOSOPHER_COUNT];

void print_status()
{
	int i=0;
	printf("\nCurrent Status:");
	for(i=0;i<PHILOSOPHER_COUNT;i++)
	{
		printf("\nPhilosopher %d : ",i);
		switch(state[i])
		{
		case 0:
			printf("thinking");
			break;
		case 1:
			printf("hungry");
			break;
		case 2:
			printf("eating");
			break;
		}
	}
}

void check(int philosopher_index) 
{
	pthread_mutex_lock(&mutex);
	if (state[philosopher_index] == HUNGRY && state[LEFT(philosopher_index)] != EATING && state[RIGHT(philosopher_index)] != EATING)
	{
		state[philosopher_index] = EATING;
		pthread_mutex_unlock(&philosopher_semaphore[philosopher_index]);
	}
	pthread_mutex_unlock(&mutex);
}

void take_chopstick(int philosopher_index)
{
		while(state[philosopher_index]!=EATING)
		{
			printf("\nPhilosopher %d is hungry",philosopher_index);
			pthread_mutex_lock(&mutex);
			state[philosopher_index]=HUNGRY;
			printf("\nPhilosopher %d trying to obtain chopsticks", philosopher_index);
			pthread_mutex_unlock(&mutex);
			check(philosopher_index);
			if(state[philosopher_index]!=EATING)
			{
				printf("\nPhilosopher %d could not obtain chopsticks",philosopher_index);
				pthread_mutex_lock(&philosopher_semaphore[philosopher_index]);
			}
		}
		printf("\nPhilosopher %d has obtained chopsticks and has started eating",philosopher_index);
		print_status();
}

void put_chopstick(int philosopher_index) 
{
	
	printf("\nPhilosopher %d has finished eating and is releasing chopsticks",philosopher_index);
	pthread_mutex_lock(&mutex);
	state[philosopher_index] = THINKING;
	pthread_mutex_unlock(&mutex);
	printf("\nPhilosopher %d is now thinking",philosopher_index);
	print_status();
	check(LEFT(philosopher_index));
	check(RIGHT(philosopher_index));
}


  
void *init(void * arg)
{
	int i=*(int *)arg;
	while(1)
	{
		sleep(rand()%10);
		take_chopstick(i);
		sleep(rand()%10);
		put_chopstick(i);
		sleep(rand()%10);
	}
}

int main()
{
	int i=0,res=0;
	pthread_t phil[PHILOSOPHER_COUNT];
	pthread_mutex_init(&mutex,NULL);
	for(i=0;i<5;i++)
	{
		state[i]=THINKING;
		pthread_mutex_init(&philosopher_semaphore[i], NULL);
	}
	printf("Generating threads");
	for(i=0;i<PHILOSOPHER_COUNT;i++)
	{
		int*arg=(int *)malloc(sizeof(int));
		*arg=i;
		pthread_create(&phil[i],NULL,init,(void *)arg);
	}
	for(i=0;i<PHILOSOPHER_COUNT;i++)
		pthread_join(phil[i],NULL);
	pthread_mutex_destroy(&mutex);
	for(i=0;i<PHILOSOPHER_COUNT;i++)
		pthread_mutex_destroy(&philosopher_semaphore[i]);
	exit(EXIT_SUCCESS);	
}
