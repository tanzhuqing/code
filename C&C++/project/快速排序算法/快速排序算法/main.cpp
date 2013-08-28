#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 18

void QuickSort(int *arr,int left,int right)
{
	int f, t;
	int rtemp,ltemp;

	ltemp = left;
	rtemp = right;
	f =arr[(left+right)/2];

	while(ltemp<rtemp)
	{
		while(arr[ltemp]<f)
		{
			++ltemp;
		}
		while(arr[rtemp]>f)
		{
			--rtemp;
		}
		if(ltemp<=rtemp)
		{
			t = arr[ltemp];
			arr[ltemp]= arr[rtemp];
			arr[rtemp]=t;
			--rtemp;
			++ltemp;
		}
	}
	if(ltemp == rtemp)
	{
		ltemp++;
	}
	if(left <rtemp)
	{
		QuickSort(arr,left,ltemp-1);
	}
	if(ltemp<right)
	{
		QuickSort(arr,rtemp+1,right);
	}
}


void main()
{
	int i;
	int shuzu[SIZE];
	srand(time(NULL));
	for(i=0;i<SIZE;i++)
	{
		shuzu[i]=rand()/1000+100;
	}
	printf("ÅÅÐòÇ°£º\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",shuzu[i]);
	}
	printf("\n");

	QuickSort(shuzu,0,SIZE-1);

	printf("ÅÅÐòºó£º\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",shuzu[i]);

	}

	printf("\n");
}