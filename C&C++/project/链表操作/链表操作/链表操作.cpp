// 链表操作.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct
{
   char key[10];                          //关键字
   char name[20];
   int age;
}Data;                                   //数据节点类型
typedef struct Node{                   //定义链表结构
  Data nodeData;
  struct Node *nextNode;
}CLType;

CLType *CLAddEnd(CLType *head,Data nodeData)   //追加节点
{
   CLType *node,*htemp;
   if(!(node=(CLType*)malloc(sizeof(CLType)))){
    printf("申请内存失败！\n");
	return NULL;
   }                                 //分配内存失败
   else{
	   node->nodeData = nodeData;          //保存数据
	   node->nextNode = NULL;               //设置结点指针为空，即为表尾
	   if(head == NULL){                    //头指针
	     head = node;
		 return head;
	   }
	   htemp = head;
	   while(htemp->nextNode != NULL)           //查找链表的末尾
	   {
		   htemp = htemp->nextNode;
	   }
	   htemp->nextNode = node;
	   return head;
   }
}

CLType *CLAddFirst(CLType *head,Data nodeData)
{
   CLType *node;
   if(!(node=(CLType *)malloc(sizeof(CLType))))
   {
      printf("申请内存失败！\n");
	  return NULL;                                 //分配内存失败
   }else{
	   node->nodeData = nodeData;                 //保存数据
	   node->nextNode = head;                    //指向头指针所指结点
	   head = node;                      //头指针指向新增结点
		   return head;            
   }
}

CLType *CLFindNode(CLType *head,char *key)              // 查找结点
{
   CLType *htemp;              
   htemp = head;                                 //保存链表指针
   while(htemp){                            //若结点有效，则进行查找
	   if(strcmp(htemp->nodeData.key,key) == 0){    //若结点关键字与传入关键字相同
	      return htemp;                           //返回该结点指针
	   }
	   htemp = htemp->nextNode;                 //处理下一个结点
   }
   return NULL;                    //返回空指针
}

CLType *CLInsertNode(CLType *head,char *findkey,Data nodeData)  //插入结点
{
  CLType *node,*nodetemp;
  if(!(node=(CLType *)malloc(sizeof(CLType)))){          //分配保存结点的内容
           printf("申请内存失败！\n");
			   return 0;                                 //分配内存失败
  }
  node->nodeData = nodeData;                   //保存节点中的数据
  nodetemp = CLFindNode(head,findkey);             
  if(nodetemp){                           //若找到要插入的节点
	  node->nextNode = nodetemp->nextNode;    // 新插入结点指向关键节点的下一节点
	  nodetemp->nextNode = node;              //设置关节节点指向新插入结点
  }
  else{
      printf("未找到正确的插入位置！\n");          
	  free(node);                  //释放内存
  }
  return head;      //返回头指针

}

int CLDeleteNode(CLType *head,char *key){
  CLType *node,*htemp;            //node保存删除节点的前一节点
  htemp = head;
  node = head;
  while(htemp){
	  if(strcmp(htemp->nodeData.key,key)==0)          //查找关键字，执行删除操作
	  {
		  node->nextNode = htemp->nextNode;   //使前一节点指向当前节点的下一节点
		  free(htemp);            //释放内存
	      return 1;
	  }
	  else{
	    node =htemp;                       //指向当前节点
		htemp = htemp->nextNode;            //指向下一节点
	  }
  }
  return 0;                         //未删除
} 


int CLLength(CLType *head)    //计算链表长度
{
	CLType *htemp;
	int Len = 0;
	htemp = head;
	while(htemp){                 //遍历整个链表
	  Len++;                               //累加节点数量
	  htemp=htemp->nextNode;           //处理下一节点
	}
	return Len;                  //返回节点数量
}


void CLAllNode(CLType *head){          //遍历链表
	CLType * htemp;
	Data nodeData;
	htemp = head;
	printf("当前链表共有%d 个节点。链表所有数据如下：\n",CLLength(head));
	while(htemp){                         //循环处理链表每个节点
		nodeData = htemp->nodeData;                 //获取节点数据
		printf("节点（%s,%s,%d）\n",nodeData.key,nodeData.name,nodeData.age);
		htemp=htemp->nextNode;                    //处理下一个节点
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CLType *node, *head = NULL;
	Data nodeData;
	char key[10],findkey[10];

	printf("链表测试。先输入链表中的数据，格式为：关键字  姓名  年龄\n");
	do{
	      fflush(stdin);           //清空缓存区
		  scanf("%s",nodeData.key);
		  if(strcmp(nodeData.key,"0")==0){
		       break;      //若输入0，则退出
		  }
		  else{
			  scanf("%s%d",nodeData.name,&nodeData.age);
			  head = CLAddEnd(head,nodeData);           //在链表尾部添加节点
		  
		  }
	
	}while(1);
	CLAllNode(head);           //显示所有节点

	printf("\n 演示插入节点，输入插入位置的关键字：");
	scanf("%s",&findkey);
	printf("输入插入结点的数据（关键字  姓名  年龄）：");
	scanf("%s%s%d",nodeData.key,nodeData.name,&nodeData.age);//输入插入结点数据
	head = CLInsertNode(head,findkey,nodeData);         //调用插入函数
	CLAllNode(head);             //显示所有节点

	printf("\n 演示删除节点，输入要删除的关键字：");
	fflush(stdin);//    清空输入缓冲区
	scanf("%s",key);   //输入删除结点关键字
	CLDeleteNode(head,key);  //调用删除节点函数
	CLAllNode(head);      //显示所有结点

	printf("\n 演示在链表中查找，输入查找关键字：");
	fflush(stdin);  //清空输入缓冲区
	scanf("%s",key);     //输入查找关键字
	node = CLFindNode(head,key);    //调用查找函数，返回节点指针
	if(node){
		nodeData = node->nodeData;              //获取节点的数据
		printf("关键字%s对应的节点为（%s,%s,%d）\n",key,nodeData.key,nodeData.name,nodeData.age);
	
	 }else{             //若结点指针无效
		 printf("在链表中未找到关键字为%s的节点！\n",key);
	}




	return 0;
}

