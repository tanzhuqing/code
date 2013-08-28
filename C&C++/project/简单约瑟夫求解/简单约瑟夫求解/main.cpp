#include<string.h>
#include<stdio.h>
#include<malloc.h>

#define Num 41
#define KillMan 3

void Josephus(int alive)
{
	int man[Num] = {0};
	int count = 1;
	int i=0,pos =-1;

	while(count <= Num)
	{
		do{
			pos = (pos+1)%Num;
			if(man[pos] == 0)
				i++;
			if(i == KillMan)
			{
				i=0;
				break;
			}
		}while(1);
		man[pos] = count;
		printf("第%2d个人自杀！约瑟夫环编号为%2d",pos+1,man[pos]);
		if(count%2)
		{
			printf("->");
		}
		else
		{
			printf("->\n");
		}
		count++;
	}

	printf("\n");
	printf("这%d需要存活的人初始位置应排在以下序号：\n",alive);
	alive = Num - alive;
	for(i=0;i<Num;i++)
	{
		if(man[i] > alive)
		{
			printf("初始编号：%d,约瑟夫环编号:%d\n",i+1,man[i]);
		}
	}
	printf("\n");
}

void main()
{
	int alive;
	printf("约瑟夫环问题求解！\n");
	printf("输入需要留存的人的数量：");
	scanf("%d ",&alive);
	fflush(stdin);
	Josephus(alive);
}