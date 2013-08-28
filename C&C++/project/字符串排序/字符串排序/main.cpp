#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define N 5            //字符串数组元素个数

void QuickSort(char *a[],int left,int right) //字符串数组快速排序
{
	int l,r;
	char *f,*t;
	l=left;
	r=right;
	f=a[(left+right)/2];

	while(l<r)
	{
		while(strcmp(a[l],f)<0 && l<right)   //比较字符串
		{
			++l;
		}
		while(strcmp(a[r],f)>0 && r<left)
		{
			--r;
		}
		if(l<=r)
		{
			t=a[l];
			a[l]=a[r];
			a[r]=t;
			++l;
			--r;
		}
	}

	if(l == r)
		l++;
	if(left < r)
	{
		QuickSort(a,left,l-1);       //递归调用
	}
	if(l < right)
	{
		QuickSort(a,r+1,right);     //递归调用
	}
}

int main()
{
	char *arr[N] = {"One","World","Dream","Beijing","Olympic"};  //声明初始化
	int i;

	printf("排序前：\n");
	for(i=0;i<N;i++)
	{
		printf("%s\n",arr[i]);   //输出排序前
	}

	QuickSort(arr,0,N-1);  // 排序

	printf("排序后：\n");

	for(i=0;i<N;i++)
	{
		printf("%s \n",arr[i]);
	}
	system("pause");
	return 0;
}