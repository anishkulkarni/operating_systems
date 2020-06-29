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
	FILE *fp;
	int pipe_fd=0;
	int res=0;
	int more=0;
	int i=0;
	int fd=0;
	int char_count=0,word_count=0,line_count=0;
	char buffer[BUFSIZ];
	char minibuf[BUFSIZ];
	memset(buffer,'\0',BUFSIZ);
	pipe_fd=open("fifo",O_RDONLY);
	printf("\nContents of the file are:\n");
	res=read(pipe_fd,buffer,BUFSIZ);
	printf("%s",buffer);
	close(pipe_fd);
	while(buffer[i]!='\0')
	{
		char_count++;
		if(buffer[i]==' ' && buffer[i+1]!=' ')
			word_count++;
		if(buffer[i]=='\n' && buffer[i+1]!='\0')
		{
			line_count++;
			word_count++;
			char_count--;
		}
		i++;
	}
	word_count++;
	line_count++;
	fp = fopen("temp.txt", "w");
	fprintf(fp, "Character Count: %d\nWord Count: %d\nLine Count: %d", char_count, word_count, line_count);
	fclose(fp);
	fp = fopen("temp.txt","r");
	fread(buffer, BUFSIZ, 1, fp);
	fclose(fp);
	//buffer[0]=char_count;
	//buffer[1]=word_count;
	//buffer[2]=line_count;
	//buffer[3]='\0';
	pipe_fd=open("fifo",O_WRONLY);
	res=write(pipe_fd,buffer,BUFSIZ);
	close(pipe_fd);
}
