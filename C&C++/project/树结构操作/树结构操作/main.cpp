#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

#define MANLEN 20  //最大长度
typedef char DATA;        //定义元素类型
typedef struct CBT    //定义二叉树节点类型
{
	DATA data;               //元素数据
	struct CBT *left;         //左子树结点指针
	struct CBT *right;        //右子树结点指针

}CBTType;


CBTType *InitTree()
{
  CBTType *node;

  if(node=(CBTType*)malloc(sizeof(CBTType)))
  {
	printf("请输入一个根节点数据：\n");
	scanf("%s",&node->data);
	node->left = NULL;
	node->right = NULL;
	if(node != NULL)
	{
		return node;
	}else
	{
		return NULL;
	}

  }
  return NULL;

}

CBTType *TreeFindNode(CBTType *treeNode,DATA data)         //查找结点
{
	CBTType *ptr;
	if(treeNode == NULL)
	{
		return NULL;
	}
	else
	{	
		if(treeNode->data == data)
		{	
			return treeNode;
		}
		else
		{
			if(ptr = TreeFindNode(treeNode->left,data))            //分别向左右子树递归查找
			{
				return ptr;
			}else if(ptr = TreeFindNode(treeNode->right,data))
			{
				return ptr;
			}
			else
			{
				return NULL;
			}
		}
	}

}


void AddTreeNode(CBTType *treeNode)
{
   CBTType *pnode,*parent;
   DATA data;
   char menusel;

   if(pnode=(CBTType *)malloc(sizeof(CBTType)))     //分配内存
   {
	printf("输入二叉树节点数据：\n");
	fflush(stdin);   //清空输入缓冲区
	scanf("%s",&pnode->data);
	pnode->left = NULL;
	pnode->right = NULL;

	printf("输入该节点的父节点数据：");
	fflush(stdin);
	scanf("%s",&data);
	parent = TreeFindNode(treeNode,data);    //查找指定数据的节点
	if(!parent)
	{
		printf("未找到该父节点！\n");
		free(pnode);                   //释放创建的节点内存
		return;
	}
	printf("1.添加该节点到左子树\n2.添加该节点到右子树\n");
		do{
		
			menusel = getch();          //输入选择项
			menusel-='0';
			if(menusel == 1 || menusel == 2)
			{
				if(parent == NULL)
				{
					printf("不存在父节点，请先设置父节点！\n");
				}
				else
				{
					switch(menusel)
					{
					case 1:                //添加到左节点
						if(parent->left)          //左节点不为空
						{
							printf("左子树节点不为空！\n");
						}
						else
						{
							parent->left = pnode;
						}
						break;
					case 2:                      //添加到右节点
						if(parent->right)    //右子树不为空
						{
							printf("右子树节点不为空！\n");
						}
						else
						{
							parent->right = pnode;
						}
						break;
					default:
						printf("无效参加！\n");
					}
				}
			}
		}while(menusel!=1 && menusel !=2);
   }
}





CBTType *TreeLeftNode(CBTType *treeNode)      //获取左子树
{
	if(treeNode)
	{
		return treeNode->left;     //返回值
	}else
	{
		return NULL;
	}
}

CBTType *TreeRightNode(CBTType *treeNode)      //获取右子树
{
	if(treeNode)
	{
		return treeNode->right;         //返回值
	}
	else
	{
		return NULL;
	}
}


int TreeIsEmpty(CBTType *treeNode)         //判断空树
{
	if(treeNode)
	{
		return 0;
	}else
	{
		return 1;
	}
}

int TreeDepth(CBTType *treeNode)        //计算二叉树深度
{
	int depleft,depright;

	if(treeNode == NULL)
	{
		return 0;            //对于空树，深度为0
	}
	else
	{
		depleft = TreeDepth(treeNode->left);  //左子树深度（递归调用）
		depright = TreeDepth(treeNode->right);  //右子树深度（递归调用）
		if(depleft>depright)
		{
			return depleft +1;
		}
		else{
			return depright + 1;
		}
	}
}


void ClearTree(CBTType * treeNode)
{
	if(treeNode)
	{
		ClearTree(treeNode->left);     //清空左子树
		ClearTree(treeNode->right);      //清空右子树
		free(treeNode);   //释放当前节点所占内存
		treeNode = NULL;
	}
}


void TreeNodeData(CBTType *p)          //显示结点数据
{
	printf("%c",p->data);            //输出结点数据
}


void LevelTree(CBTType *treeNode,void(*TreeNodeData)(CBTType *p))   //按层遍历
{
	CBTType *p;
	CBTType *q[MANLEN];  //定义一个顺序栈
	int head = 0,tail = 0;

	if(treeNode)                    //如果队首指针不为空
	{
		tail = (tail+1)%MANLEN;            //计算循环队列队尾序号
		q[tail] = treeNode;                 //将二叉树根指针进队
	}
	while(head!=tail)                    //队列不为空，进行循环
	{ 
		head = (head +1)%MANLEN;           //计算循环队列的队首序号
		p=q[head];                  //获取队首元素
		TreeNodeData(p);      //处理队首元素
		if(p->left!=NULL)      //如果节点存在左子树
		{
			tail = (tail+1)%MANLEN; //计算循环队列的队尾序号
			q[tail] = p->left;         //将左子树指针进队
		}

		if(p->right != NULL)          //如果结点存在右子树
		{
			tail = (tail + 1)%MANLEN;    //计算循环队列的队尾序号
			q[tail] = p->right;        //将右子树指针进队
		}
	}
}


void DLRTree(CBTType *treeNode,void (*TreeNodeData)(CBTType *p))  //先序遍历
{
	if(treeNode)
	{
		TreeNodeData(treeNode);           //显示结点的数据
		DLRTree(treeNode->left,TreeNodeData);
		DLRTree(treeNode->right,TreeNodeData);
	}
}

void LDRTree(CBTType *treeNode,void(*TreeNodeData)(CBTType *p))   //中序遍历
{
	if(treeNode)
	{
		LDRTree(treeNode->left,TreeNodeData);
		TreeNodeData(treeNode);
		LDRTree(treeNode->right,TreeNodeData);
	}
}

void LRDTree(CBTType *treeNode,void(*TreeNodeData)(CBTType *p))  //后序遍历
{
	if(treeNode)
	{
		LRDTree(treeNode->left,TreeNodeData);
		LRDTree(treeNode->right,TreeNodeData);
		TreeNodeData(treeNode);
	}
}



void main()
{
	CBTType *root=NULL;
	char  menusel;
	void (*TreeNodeData1)(CBTType *p);
	TreeNodeData1=TreeNodeData;

	root = InitTree();
	do{
		printf("请选择菜单添加二叉树的节点\n");
		printf("0.退出\t");
		printf("1.添加二叉树的节点\n");
		menusel = getch();
		switch(menusel)
		{
		case '1':
			AddTreeNode(root);
			break;
		case '0':
			break;
		default:
			;
		}
	}while(menusel != '0');

	do{
		printf("请选择菜单遍历二叉树，输入0表示退出：\n");
		printf("1.先序遍历DLR\t");
		printf("2.中序遍历LDR\n");
		printf("3.后序遍历LRD\t");
		printf("4.按层遍历\n");


		menusel = getch();
		switch(menusel)
		{
		case '0':
			break;
		case '1':
			printf("\n 先序遍历DLR的结果：");
			DLRTree(root,TreeNodeData1);
			printf("\n");
			break;
		case '2':
			printf("\n中序遍历LDR的结果：");
			LDRTree(root,TreeNodeData1);
			printf("\n");
			break;
		case '3':
			printf("\n 后序遍历LRD的结果：");
			LRDTree(root,TreeNodeData1);
			printf("\n");
			break;
		case '4':
			printf("\n 按层遍历的结果：");
			LevelTree(root,TreeNodeData1);
			printf("\n");
			break;
		default:
			;
		}
	
	}while(menusel != '0');

	printf("\n 二叉树深度为：%d \n",TreeDepth(root));

	ClearTree(root);
	root = NULL;


}

