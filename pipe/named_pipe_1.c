#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
	int pipe_fd=0;
	int res=0;
	int more=0;
	char buffer[BUFSIZ];
	char minibuf[BUFSIZ];
	char newl[2]={'\n','\0'};
	memset(buffer,'\0',BUFSIZ);
	pipe_fd=open("fifo",O_WRONLY);
	do
	{
		printf("\nEnter line: ");
		scanf("%[^\n]", minibuf);
		strcat(buffer,minibuf);
		printf("\nDo you want to write more?(1=yes, 0=no): ");
		scanf("%d",&more);
		strcat(buffer,newl);
		while(getchar()!='\n');
	}while(more==1);
	res=write(pipe_fd,buffer,BUFSIZ);
	close(pipe_fd);
	pipe_fd=open("fifo",O_RDONLY);
	res=read(pipe_fd,buffer,BUFSIZ);
	close(pipe_fd);
	//printf("\nCharacter count: %d",buffer[0]);
	//printf("\nWord count: %d",buffer[1]);
	//printf("\nLine count: %d",buffer[2]);
	printf("%s",buffer);
	printf("\n");
}
