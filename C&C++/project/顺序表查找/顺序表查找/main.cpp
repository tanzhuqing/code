#include<stdio.h>
#include<string.h>

#define MAXLEN 100

typedef struct
{
	char key[10];
	char name[20];
	int age;
}DATA;

typedef struct
{
	DATA ListData[MAXLEN + 1];
	int ListLen;
}SLType;

void SLInit(SLType *SL)
{
	SL->ListLen = 0;
}

int SLLength(SLType *SL)
{
	return (SL->ListLen);
}

int SLAdd(SLType *SL,DATA data)
{
	if(SL->ListLen >= MAXLEN)
	{
		printf("顺序表已满，不能再添加节点了！\n");
			return 0;
	}

	SL->ListData[++SL->ListLen] = data;
	return 1;
}


DATA *SLFindByNum(SLType *SL,int n)
{
	if(n<1 || n>SL->ListLen +1)
	{
		printf("结点序号错误，不能返回节点！\n");
		return NULL;
	}
	return &(SL->ListData[n]);
}

int SLFindByCont(SLType *SL,char *key)
{
	int i;
	for(i=0;i<=SL->ListLen;i++)
	{
		if(strcmp(SL->ListData[i].key,key) == 0)
		{
			return i;
		}
	}
	return 0;
}

int SLAll(SLType *SL)
{
	int i;
	for(i=1;i<=SL->ListLen;i++)
	{
		printf("(%s,%s,%d)\n",SL->ListData[i].key,SL->ListData[i].name,SL->ListData[i].age);
	}
	return 0;
}


void main()
{
	int i;
	SLType SL;
	DATA data;
	DATA *pdata;

		printf("顺序表操作演示！\n");
		SLInit(&SL);
		printf("初始化顺序表完成!\n");

		do{
			printf("输入添加的节点（学号 姓名 年龄）：");
			fflush(stdin);
			scanf("%s %s %d",&data.key,&data.name,&data.age);
			if(data.age)
			{
				if(!SLAdd(&SL,data))
				{
					break;
				}
			}
			else
			{
				break;
			}
		}while(1);

		printf("\n顺序表中的结点顺序为：\n");
		SLAll(&SL);

		fflush(stdin);
		printf("\n要取出节点的序号：");
		scanf("%d",&i);
		pdata = SLFindByNum(&SL,i);
		if(pdata)
		{
			printf("第%d个结点为：（%s，%s，%d）\n",i,pdata->key,pdata->name,pdata->age);
		}


}