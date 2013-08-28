#include<stdio.h>

int qiongju(int head,int foot,int *chicken,int *rabbit)
{
	int re,i,j;
	re = 0;
	for(i=0;i<=head;i++)
	{
		j = head - i;
			if(i*2 + j*4 == foot){
				re = 1;
				*chicken = i;
				*rabbit = j;
				
			}
	}
	return re;
}

void main()
{
	int chicken,rabbit,head,foot;
	int re;

	printf("穷举法求解鸡笼同笼问题：\n");
	printf("输入头数：");
	scanf("%d",&head);
	printf("输入脚数：");
	scanf("%d",&foot);

	re = qiongju(head,foot,&chicken,&rabbit);

	if(re == 1)
	{
		printf("鸡有：%d只，兔子有：%d只。\n",chicken,rabbit);
	}
	else{
	  printf("无法求解！\n");
	}
}