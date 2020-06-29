#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<time.h>

void *thread_function(void *arg)
{
	int *i=(int *)malloc(sizeof(int));
	int *ret;
	ret=(int *)arg;
	*i=ret[0]*ret[1];
	pthread_exit((void *)i);
}

void display_matrix(int *m,int r,int c)
{
	int i=0,j=0;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("\t %d",*(m + i*c + j));
		}
		printf("\n");
	}
}

void input_matrix(int *m,int r,int c)
{
	int i=0,j=0;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("Element[%d][%d]:",i,j);
			scanf("\t %d",(m + i*c + j));
		}
	}
}

int *matrix_multiply(int *m1,int *m2,int r,int c,int l)
{
	int i=0,j=0,k=0,*mat_res=(int *)malloc(r*c*sizeof(int));
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			*(mat_res + (i * c) + j)=0;
			for(k=0;k<l;k++)
			{
				*(mat_res + (i * c) + j)+=(*(m1 + (i * l) + k))*(*(m2 + (k * c) + j));
			}
		}
	}
	return mat_res;
}

int *threaded_matrix_multiply(int *m1,int *m2,int r,int c,int l)
{
	pthread_t a_thread;
	void *thread_result;
	int thread_argument[2]={0,0},res=0;
	int i=0,j=0,k=0,*mat_res=(int *)malloc(r*c*sizeof(int));
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			*(mat_res + (i * c) + j)=0;
			for(k=0;k<l;k++)
			{
				thread_argument[0]=*(m1 + i*l + k);
				thread_argument[1]=*(m2 + k*c + j);
				res=pthread_create(&a_thread,NULL,thread_function,(void *)thread_argument);
				if(res!=0)
				{
					perror("Thread creation failed");
					exit(EXIT_FAILURE);
				}
				res=pthread_join(a_thread,&thread_result);
				if(res!=0)
				{
					perror("Thread join failed");
					exit(EXIT_FAILURE);
				}
				*(mat_res + (i * c) + j)+=*((int *)thread_result);
				free(thread_result);
			}
		}
	}
	return mat_res;
}

int main()
{
	double time_taken;
	clock_t t;
	int *mat1,*mat2,*mat_r=NULL,r1=0,c1=0,r2=0,c2=0,i=0,j=0,k=0;
	printf("\nEnter the dimensions of the first matrix:");
	printf("\nRows: ");
	scanf("%d",&r1);
	printf("Columns: ");
	scanf("%d",&c1);
	printf("Enter the dimensions of the first matrix:");
	printf("\nRows: ");
	scanf("%d",&r2);
	printf("Columns: ");
	scanf("%d",&c2);
	if(r2==c1)
	{
		mat1=(int *)malloc(r1*c1*sizeof(int));
		mat2=(int *)malloc(r2*c2*sizeof(int));
		printf("\nEnter the elements of the first matrix:\n");
		input_matrix(mat1,r1,c1);
		printf("\nEnter the elements of the second matrix:\n");
		input_matrix(mat2,r2,c2);
		printf("\nMatrix multiplication without using threads:\n");
		t = clock();
		mat_r=matrix_multiply((int *)mat1,(int *)mat2,r1,c2,c1);
		t = clock() - t;
		printf("\nResult of multiplication is:\n\n");
		display_matrix(mat_r,r1,c2);
		time_taken = ((double)t)/CLOCKS_PER_SEC;
    		printf("\nMultiplication without threads took %f seconds to execute.", time_taken); 
		printf("\n\nMatrix multiplication using threads:\n");
		t = clock() - t;
		mat_r=threaded_matrix_multiply(mat1,mat2,r1,c2,r2);
		time_taken = ((double)t)/CLOCKS_PER_SEC;
		printf("\nResult of multiplication is:\n\n");
		display_matrix(mat_r,r1,c2);
    		printf("\nMultiplication using threads took %f seconds to execute.", time_taken); 
	}
	else
	{
		printf("\nInvalid input, matrix multiplication not possible");
	}
	printf("\n");
	exit(EXIT_SUCCESS);
}
