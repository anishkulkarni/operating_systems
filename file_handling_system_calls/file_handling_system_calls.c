#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Employee
{
    char id[10];
    char name[50];
    char department[20];
};

int main()
{
    int choice=0, fd=0, fd2=0, i=0, deleteFlag=0;
    struct Employee emp;
    char buffer[80], id[10];
    while(1)
    {
        printf("Menu\n1. Add Record\n2. Read All Recordes\n3. Delete Record\n4. Search\n5. Update\n6. Exit\nChoice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("\nEnter id: ");
                scanf("%s",emp.id);
                printf("Enter name: ");
                scanf("%s",emp.name);
                printf("Enter department: ");
                scanf("%s",emp.department);
                fd=open("data.txt",O_CREAT|O_WRONLY|O_APPEND);
                for(i=0;i<10;i++)
                    buffer[i]=emp.id[i];
                for(i=10;i<60;i++)
                    buffer[i]=emp.name[i-10];
                for(i=60;i<80;i++)
                    buffer[i]=emp.department[i-60];
                write(fd,buffer,80);
                close(fd);
                printf("Data Successfully Recorded\n\n");
                break;
            case 2:
                printf("\nFollowing records are present in the file:");
                fd=open("data.txt",O_RDONLY);
                while(read(fd,buffer,80)>0)
                {
                    printf("\nEmployee id: ");
                    for(i=0;i<10;i++)
                    {
                        if(buffer[i]=='\0')
                            break;
                        printf("%c",buffer[i]);
                    }
                    printf("\nEmployee name: ");
                    for(i=10;i<60;i++)
                    {
                        if(buffer[i]=='\0')
                            break;
                        printf("%c",buffer[i]);
                    }
                    printf("\nEmployee department: ");
                    for(i=60;i<80;i++)
                    {
                        if(buffer[i]=='\0')
                            break;
                        printf("%c",buffer[i]);
                    }
                }
                printf("\n\n");
                close(fd);
            break;
            case 3:
                fd=open("data.txt",O_RDONLY);
                fd2=open("temp.txt",O_CREAT|O_WRONLY|O_APPEND);
                printf("\nEnter id to delete: ");
                scanf("%s",id);
                while(read(fd,buffer,80)>0)
                {
                    deleteFlag=0;
                    for(i=0;i<10;i++)
                    {
                        if(buffer[i]=='\0')
                        {
                            if(id[i]!='\0')
                            {
                                deleteFlag=1;
                            }
                            break;
                        }
                        if(id[i]=='\0')
                        {
                            deleteFlag=1;
                            break;
                        }
                        if(id[i]!=buffer[i])
                        {
                            deleteFlag=1;
                            break;
                        }
                    }
                    if(deleteFlag==1)
                    {
                        write(fd2,buffer,80);
                    }
                }
                close(fd);
                close(fd2);
                remove("data.txt");
                rename("temp.txt","data.txt");
                printf("\nDelete Successfull\n\n");
            break;
            case 4:
                fd=open("data.txt",O_RDONLY);
                printf("\nEnter id to search: ");
                scanf("%s",id);
                while(read(fd,buffer,80)>0)
                {
                    deleteFlag=0;
                    for(i=0;i<10;i++)
                    {
                        if(buffer[i]=='\0')
                        {
                            if(id[i]!='\0')
                            {
                                deleteFlag=1;
                            }
                            break;
                        }
                        if(id[i]=='\0')
                        {
                            deleteFlag=1;
                            break;
                        }
                        if(id[i]!=buffer[i])
                        {
                            deleteFlag=1;
                            break;
                        }
                        if(deleteFlag==0)
                        {
                            printf("\nFollowing Record found: ");
                            printf("\nEmployee id: ");
                            for(i=0;i<10;i++)
                            {
                                if(buffer[i]=='\0')
                                    break;
                                printf("%c",buffer[i]);
                            }
                            printf("\nEmployee name: ");
                            for(i=10;i<60;i++)
                            {
                                if(buffer[i]=='\0')
                                    break;
                                printf("%c",buffer[i]);
                            }
                            printf("\nEmployee department: ");
                            for(i=60;i<80;i++)
                            {
                                if(buffer[i]=='\0')
                                    break;
                                printf("%c",buffer[i]);
                            }
                        }
                    }
                }
                printf("\n\n");
                close(fd);
            break;
            case 5:
                fd=open("data.txt",O_RDONLY);
                fd2=open("temp.txt",O_CREAT|O_WRONLY|O_APPEND);
                printf("\nEnter id to search: ");
                scanf("%s",id);
                printf("\nEnter new information");
                printf("\nEnter id: ");
                scanf("%s",emp.id);
                printf("Enter name: ");
                scanf("%s",emp.name);
                printf("Enter department: ");
                scanf("%s",emp.department);
                while(read(fd,buffer,80)>0)
                {
                    deleteFlag=0;
                    for(i=0;i<10;i++)
                    {
                        if(buffer[i]=='\0')
                        {
                            if(id[i]!='\0')
                            {
                                deleteFlag=1;
                            }
                            break;
                        }
                        if(id[i]=='\0')
                        {
                            deleteFlag=1;
                            break;
                        }
                        if(id[i]!=buffer[i])
                        {
                            deleteFlag=1;
                            break;
                        }
                    }
                    if(deleteFlag==0)
                    {  
                        for(i=0;i<10;i++)
                            buffer[i]=emp.id[i];
                        for(i=10;i<60;i++)
                            buffer[i]=emp.name[i-10];
                        for(i=60;i<80;i++)
                            buffer[i]=emp.department[i-60];
                        write(fd2,buffer,80);
                    }
                    else
                    {
                        write(fd2,buffer,80);
                    }
                }
                close(fd);
                close(fd2);
                remove("data.txt");
                rename("temp.txt","data.txt");
                printf("\nUpdate Successfull\n\n");
            break;
            case 6:
                printf("\nSuccessfull Exit\n");
                exit(EXIT_SUCCESS);
            break;
        }
    }
    return 0;
}