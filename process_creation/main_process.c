#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int a[10]={0},i=0,j=0,temp=0;
	pid_t pid;
	char a_char[10]={0};
	printf("\nEnter 10 numbers into the array:\n");
	for(i=0;i<10;i++)
	{
		printf("Number %d: ",i);
		scanf("%d",&a[i]);
	}
	printf("\n");
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
   	for(i=0;i<10;i++)
   		a_char[i]=a[i];
	pid = fork();
	if(pid == 0)
	{
		char *argv[]={a_char,NULL};
		execv("./called_process",argv);
	}
	if(pid>0)
    	{
       		wait(NULL);
	}
}
