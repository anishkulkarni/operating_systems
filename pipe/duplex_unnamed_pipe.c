#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
	if(argc==2)
	{
		//valid arguments
		FILE *fp;
		void *read_status=NULL;
		int data_processed;
		int i=0;
		int file_pipes_p2c[2];
		//int file_pipes_c2p[2];
		char buffer[BUFSIZ + 1];
		pid_t pid;
		memset(buffer, '\0', sizeof(buffer));
		if (pipe(file_pipes_p2c) == 0 /*&& pipe(file_pipes_c2p)==0*/)
		{
			//pipe creation successfull
			pid=fork();
			if(pid==0)
			{
				//child process
				data_processed = read(file_pipes_p2c[0], buffer, BUFSIZ);
				close(file_pipes_p2c[0]);
				printf("Opening file %s\nContents are:\n\n",buffer);
				fp=fopen(buffer,"r");
				fread(buffer,sizeof(buffer),1,fp);
				data_processed = write(file_pipes_p2c[1],buffer, strlen(buffer));
				close(file_pipes_p2c[1]);
			}
			else if(pid>0)
			{
				//parent process
				data_processed = write(file_pipes_p2c[1],argv[1], strlen(argv[1]));
				close(file_pipes_p2c[1]);
				wait(NULL);
				data_processed = read(file_pipes_p2c[0], buffer, BUFSIZ);
				close(file_pipes_p2c[0]);
				printf("%s",buffer);
			}
			else
			{
				//fork unsuccessfull
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			//pipe creation unsuccessful
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		//invalid arguments
		printf("Invalid arguments, terminating");
	}
}
