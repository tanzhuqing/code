#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10


void InsertionSort(int *a, int len)
{
	int i,j,t,h;

	for(i=1;i<len;i++)
	{
		t = a[i];
		j=i-1;
		while(j>=0 && t<a[j])
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = t;
		printf("第%d步排序结果：",i);

		for(h = 0;h<len;h++)
		{
			printf("%d ",a[h]);
		}
		printf("\n");
	}
}

void main()
{
	int arr[SIZE],i;

	srand(time(NULL));

	for(i=0;i<SIZE;i++)
	{
		arr[i] = rand()/1000 + 100;
	}

	printf("排序前：\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

	InsertionSort(arr,SIZE);

	printf("排序后:\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}