#include<stdio.h>

int binary_search(int arr[], int l, int r, int x) 
{ 
    if (r >= l) 
   { 
        int mid = l + (r - l) / 2; 
        if (arr[mid] == x) 
            return mid;
        if (arr[mid] > x) 
            return binary_search(arr, l, mid - 1, x);
        return binary_search(arr, mid + 1, r, x); 
    }
    return -1; 
}

int main(int argc, char **argv)
{
	int i,key=0,flag=0,a[10];
	printf("\nEnter the number to search: ");
	scanf("%d",&key);
	printf("\nSorted array is:\n");
	for(i=0;i<10;i++)
	{
		printf("%d\t",argv[0][i]);
		a[i]=argv[0][i];
	}
	if((flag=binary_search(a,0,9,key))!=-1)
		printf("\n\nElement found at: %d\n",flag+1);
	else
		printf("\n\nElement not found\n");
}
