#include<stdlib.h>
#include<stdio.h>
#include<string.h>


#define MAXLEN 50          //最大长度
#define SIZE 10

typedef struct
{
  char name[10];
  int age;
}DATA;

typedef struct stack
{
  DATA data[SIZE+1];             //数据元素
  int top;                     // 栈顶
}StackType;

StackType *STInit()
{
	StackType *p;
	if(p=(StackType*)malloc(sizeof(StackType))){       //申请栈内存
		p->top=0;                //设置栈顶为0
		return p;                //返回指向栈的指针
	}
	return NULL;
}

int STIsEmpty(StackType *s)   //判断栈是否为空
{
   int t;
   t = (s->top==0);
   return t;
}

int STIsFull(StackType *s)      //判断栈是否已满
{
   int t;
   t = (s->top == MAXLEN);
   return t;
}

void STClear(StackType *s){          //清空栈
	s->top =0;

}

void  STFree(StackType *s)       //释放栈所占用的空间
{
  if(s)
  {
    free(s);
  }
}

int PushST(StackType *s,DATA data)     //入栈操作
{
	if((s->top+1)>MAXLEN)
	{
	  printf("栈溢出！\n");
		  return 0;
	}
	s->data[++s->top]=data;      //将元素入栈
	return 1;
}

DATA PopST(StackType *s)           //出栈操作
{
	if(s->top == 0)
	{
	  printf("栈为空！\n");
		  exit(0);
	}
	return (s->data[s->top--]);
}

DATA PeekST(StackType *s)      //读栈顶数据
{
	if(s->top==0)
	{
	  printf("栈为空！\n");
	  exit(0);
	}
	return (s->data[s->top]);
}


void main()
{
  StackType *stack;
  DATA data,data1;
  
  stack = STInit();
  printf("入栈操作:\n");
  printf("输入姓名 年龄进行入栈操作：");
  do
  {
	  scanf("%s%d",data.name,&data.age);
	  if(strcmp(data.name,"0")==0)
	  {
	    break;                     //若输入0，则退出
	  }else
	  {
	    PushST(stack,data);
	  }

  }while(1);

  do
  {
   printf("\n出栈操作：按任意键进行出栈操作：");
   getchar();
   data1 = PopST(stack);
   printf("出战的数据是（%s,%d）",data1.name,data1.age);
  
  }while(1);
  STFree(stack);                        //释放栈所占用的空间
}