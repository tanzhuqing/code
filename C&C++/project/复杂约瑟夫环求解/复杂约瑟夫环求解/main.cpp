#include<string.h>
#include<stdio.h>
#include<malloc.h>

typedef struct node
{
	int number;
	int psw;
	struct node *next;
}LNode,*LinkList;

void insertList(LinkList *list,LinkList q,int number,int psw)
{
	LinkList p;

	p=(LinkList)malloc(sizeof(LNode));
	p->number = number;
	p->psw = psw;

	if(!*list)
	{
		*list = p;
		p->next = NULL;
	}
	else
	{
		p->next = q->next;
		q->next = p;
	}
}

void CircleFun(LinkList *list,int m)
{
	LinkList p,q;
	int i;
	p=q=*list;
	while(q->next != p)
	{
		q = q->next;
	}

	printf("游戏者按照如下的顺序出列。\n");
	while(p->next != p)
	{
		for(i=0;i<m;i++)
		{
			q =p;
			p = p->next;
		}
		q->next = p->next;
		printf("第%d个人出列，其手中的出列数字为%d.\n",p->number,p->psw);
		m = p->psw;
		free(p);
		p=q->next;
	}
	printf("最后一个人是%d,其手中的出列数字为%d。",p->number,p->psw);
}


void main()
{
	LinkList list1 = NULL,q=NULL,list;
	int num,baoshu;

	int i,e;
	printf("约瑟夫问题求解！\n");
	printf("请输入约瑟夫环中的人数：\n");
	scanf("%d",&num);

	printf("按照顺序输入每个人手中的出列数字：\n");

	for(i=0;i<num;i++)
	{
		scanf("%d",&e);
		insertList(&list1,q,i+1,e);
		if(i == 0)
		{
			q=list1;
		
		}else
		{
			q=q->next;
		}
	}
	q->next = list1;
	list = list1;

	printf("请输入第一次出列的数字：\n");
	scanf("%d",&baoshu);
	CircleFun(&list,baoshu);
	printf("\n");
}