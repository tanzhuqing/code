#include<string.h>
#include<stdio.h>
#include<malloc.h>


typedef struct node
{
	char data;
	struct node *next;
}LNode,*LinkList;

LinkList CreatLinkList()
{
	char ch;
	LinkList list = NULL;

	scanf("%c",&ch);
	list = (LinkList)malloc(sizeof(LNode));
	list->data = ch;
	list->next = NULL;

	return list;
}

void insertList(LinkList *list,LinkList q,char e)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = e;
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

void DynamicSort(LinkList q)
{
	LNode *p = q;
	int i,j,k=0;
	char t;

	while(p)
	{
		k++;
		p=p->next;
	}
	p=q;
	for(i=0;i<k;i++)
	{
		for(j=0;j<k-i-1;j++)
		{
			if(p->data > p->next->data)
			{
				t=p->data;
				p->data = p->next->data;
				p->next->data = t;
			}
			p = p->next;
		}
		p=q;
	}
}

void main()
{
	char ch;
	LinkList list,q;

	printf("动态数组排序！\n");
	printf("请输入一组字符，以0结束！\n");
	q=list=CreatLinkList();

	scanf("%c",&ch);
	while(ch != '0')
	{
		insertList(&list,q,ch);
		q=q->next;
		scanf("%c",&ch);
	}

	DynamicSort(list);
	printf("\n");
	printf("对该数据排序之后，得到如下结果：\n");
	while(list)
	{
		printf("%c ",list->data);
		list=list->next;
	}
	printf("\n");
}