#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int a[10]={0},i=0,j=0,temp=0;
	printf("\nEnter 10 numbers into the array:\n");
	for(i=0;i<10;i++)
	{
		printf("Number %d: ",i);
		scanf("%d",&a[i]);
	}
	printf("Elements before sorting are: ");
	for(int i=0;i<10;i++)
	{
		printf("\n%d",a[i]);
	}
	printf("\n");
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		printf("\nSorting in child process");
        	for(i=0;i<10;i++)
        	{
        		for(j=0;j<(9-i);j++)
        		{
        			if(a[j+1]<a[j])
        			{
        				temp=a[j+1];
        				a[j+1]=a[j];
        				a[j]=temp;
				}
        		}
        	}
        	printf("\nSorted elements are: ");
		for(int i=0;i<10;i++)
		{
			printf("\n%d",a[i]);
		}
		printf("\n");
		//sleep(10);//add for orphan process demonstration
	}
	if(pid>0)
        {
        	wait(NULL);
        	printf("\nSorting in parent process");
        	for(i=0;i<10;i++)
        	{
        		for(j=0;j<(9-i);j++)
        		{
        			if(a[j+1]<a[j])
        			{
        				temp=a[j+1];
        				a[j+1]=a[j];
        				a[j]=temp;
				}
        		}
        	}
        	printf("\nSorted elements are: ");
		for(int i=0;i<10;i++)
		{
			printf("\n%d",a[i]);
		}
		printf("\n");
		//sleep(10);//add for zombie process demonstration
	}
	printf("\n");
}
