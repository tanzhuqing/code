#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10


void MergeOne(int a[],int b[],int n,int len)     //完成一遍合并的函数
{
	int i,j,k,s,e;

	s=0;

	while((s+len) < n)
	{
		e = s+2*len-1;
		if(e>=n)
		{
			e=n-1;
		}

	   //相邻有序段合并
		k=s;
		i=s;
		j=s+len;

		while(i<(s+len)&&(j<=e))
		{
			if(a[i]<=a[j])
			{
				b[k++]=a[i++];
			}
			else
			{
				b[k++]=a[j++];
			}
		}
		while(i<(s+len))
		{
			b[k++]=a[i++];
		}
		while(j<=e)
		{
			b[k++]=a[j++];
		}
		s=e+1;
	}

	if(s<n)
	{
		for(;s<n;s++)
		{
			b[s] = a[s];
		}
	}
}

void MergeSort(int a[],int n)    //合并排序
{
	int *p;
	int h,count,len,f;

	count = 0;   //排序步骤
    len = 1; //有序序列的长度
	f =0;     //变量f作标志
	if(!(p=(int*)malloc(sizeof(int)*n)))  //分配内存空间
	{
		printf("内存分配失败！\n");
		exit(0);
	}
	while(len<n)
	{
		if(f == 1)
		{
			MergeOne(p,a,n,len);
		}
		else
		{
			MergeOne(a,p,n,len);
		}
		len = len*2;    //增加有序序列长度
		f=1-f;     //使f值在0和1之间切换

		count++;
		printf("第%d步排序结果：",count);
		for(h=0;h<SIZE;h++)
		{
			printf("%d ",a[h]);
		}
		printf("\n");
	}
	if(f)
	{
		for(h=0;h<n;h++)
		{
			a[h] =p[h];
		}
	}
	free(p);

}

void main()
{
	int i;
	int shuzu[SIZE];

	srand(time(NULL));
	for(i=0;i<SIZE;i++)
	{
		shuzu[i] = rand()/1000 + 100;
	}

	printf("排序前：\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",shuzu[i]);
	}
	printf("\n\n");

	MergeSort(shuzu,SIZE);

	printf("排序后：\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",shuzu[i]);
	}

	printf("\n\n");
}