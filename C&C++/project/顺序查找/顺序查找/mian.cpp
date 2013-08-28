#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 15

int SearchFun(int a[],int n,int x)
{
	int i,f = -1;
	for(i=0;i<n;i++)
	{
		if(x == a[i])
		{
			f = i;
			break;
		}
	}
	return f;
}

void main()
{
	int x,n,i;
	int shuzu[N];

	srand(time(NULL));
	for(i=0;i<N;i++)
	{
		shuzu[i] = rand()/1000 +100;

	}


	printf("顺序查找算法演示！\n");
		printf("数据列表：\n");
		for(i=0;i<N;i++)
		{
			printf("%d  ",shuzu[i]);
		}
		printf("\n\n");
		printf("输入要查找的数：");
		scanf("%d",&x);

		n=SearchFun(shuzu,N,x);

		if(n<0)
		{
			printf("没找到数据：%d\n",x);
		}else
		{
			printf("数据：%d 位于数组的第%d 个元素处.\n",x,n+1);
		}
}