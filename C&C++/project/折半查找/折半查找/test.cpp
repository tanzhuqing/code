#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 15

void QuickSort(int *arr,int left,int right)
{
	int f,t;
	int rtemp,ltemp;

	ltemp = left;
	rtemp = right;
	f = arr[(left+right)/2];
	while(ltemp < rtemp)
	{
		while(arr[ltemp] < f)
		{
			++ltemp;
		}
		while(arr[rtemp] > f)
		{
			--rtemp;
		}
		if(ltemp <= rtemp)
		{
			t = arr[ltemp];
			arr[ltemp] = arr[rtemp];
			arr[rtemp] = t;
			--rtemp;
			++ltemp;
		}
	}

	if(ltemp == rtemp)
	{
		ltemp++;

	}

	if(left < rtemp)
	{
		QuickSort(arr,left,ltemp-1);
	}
	if(ltemp <right)
	{
		QuickSort(arr,rtemp+1,right);
	}
}

int SearchFun(int a[],int n,int x)
{
	int mid,low,high;
	low =0;
	high = n-1;
	while(low <= high)
	{
		mid = (low+high)/2;
		if(a[mid] == x)
			return mid;
		else if(a[mid] > x)
			high = mid -1;
		else
			low = mid + 1;
	}
	return -1;
}

void main()
{
	int shuzu[N],x,n,i;

	srand(time(NULL));

	for(i=0;i<N;i++)
	{
		shuzu[i] = rand()/1000 + 100;
	}
	printf("折半查找算法演示！\n");
	printf("排序前数据序列：\n");

	for(i=0;i<N;i++)
	{
		printf("%d ",shuzu[i]);
	}
	printf("\n\n");

	QuickSort(shuzu,0,N-1);
	printf("排序后数据序列：\n");
	for(i=0;i<N;i++)
	{
		printf("%d ",shuzu[i]);
	}
	printf("\n\n");
	printf("输入要查找的数：");
	scanf("%d ",&x);

	n = SearchFun(shuzu,N,x);

	if(n < 0)
	{
		printf("没找到数据：%d ",x);

	}
	else
	{
		printf("数据%d 位于数组的第%d个元素处.\n",x,n+1);
	}
}