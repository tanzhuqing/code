// 反序排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define SIZE 10  //数组大小


void InsertionSort(int *a,int len){   //插入排序
	int i,j,t,h;
	for(i=1;i<len;i++){
		t = a[i];
		j = i-1;
		while(j>=0&&t>a[j])  //反序
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = t;

		printf("第%d步排序结果：",i);   //输出每步排序的结果
		for(h=0;h<len;h++)
		{
			printf("%d ",a[h]);    //输出
		}
		printf("\n");
	}
}

void main()
{
	int arr[SIZE],i;  //声明数组

	srand(time(NULL));
	for(int i=0;i<SIZE;i++)
	{
		arr[i] = rand()/1000 + 100;
	}
	printf("排序前：\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",arr[i]);    //输出
	}

	printf("\n");

	InsertionSort(arr,SIZE);    //反序排序

	printf("排序后：\n");

	for(i=0;i<SIZE;i++)
	{
		printf("%d ",arr[i]);  //输出
	}

	printf("\n");
}




