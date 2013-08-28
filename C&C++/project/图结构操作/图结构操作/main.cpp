#include<stdio.h>

#define MaxNum 20
#define MaxValue 65535

typedef struct
{
	char Vertex[MaxNum];
	int GType;
	int VertexNum;
	int EdgeNum;
	int EdgeWeight[MaxNum][MaxNum];
	int isTrav[MaxNum];
}GraphMatrix;

void CreateGraph(GraphMatrix *GM)
{
	int i,j,k;
	int weight;
	char EstartV,EendV;

	printf("输入图中各顶点信息\n");
	for(i=0;i<GM->VertexNum;i++)
	{
		getchar();
		printf("第%d个顶点:",i+1);
		scanf("%c",&(GM->Vertex[i]));
	}

	printf("输入构成各边的顶点及权值：\n");
	for(k=0;k<GM->EdgeNum;k++)
	{
		getchar();
		printf("第%d条边:",k+1);
		scanf("%c %c %d",&EstartV,&EendV,&weight);
		for(i=0;EstartV!=GM->Vertex[i];i++);
		for(j=0;EendV!=GM->Vertex[j];j++);
		GM->EdgeWeight[i][j]=weight;
		if(GM->GType == 0)
		{
			GM->EdgeWeight[j][i] = weight;

		}
	}
}

void ClearGraph(GraphMatrix *GM)
{
	int i,j;
	for(i=0;i<GM->VertexNum;i++)
	{
		for(j=0;j<GM->VertexNum;j++)
		{
			GM->EdgeWeight[i][j] = MaxValue;
		}
	}
}


void OutGraph(GraphMatrix * GM)
{
	int i,j;
	for(j=0;j<GM->VertexNum;j++)
	{
		printf("\t%c",GM->Vertex[j]);
	}
	printf("\n");
	for(i=0;i<GM->VertexNum;i++)
	{
		printf("%c",GM->Vertex[i]);
		for(j=0;j<GM->VertexNum;j++)
		{
			if(GM->EdgeWeight[i][j] == MaxValue)
			{
				printf("\tZ");  //Z表示无穷大
			}else
			{
				printf("\t%d",GM->EdgeWeight[i][j]);
			}
		}
		printf("\n");
	}
}

void DeepTraOne(GraphMatrix *GM, int n)
{
	int i;
	GM->isTrav[n] = 1;
	printf("->%c",GM->Vertex[n]);

	for(i=0;i<GM->VertexNum;i++)
	{
		if(GM->EdgeWeight[n][i] != MaxValue && !GM->isTrav[n])
		{
			DeepTraOne(GM,i);
		}
	}
}


void DeepTraGraph(GraphMatrix *GM)
{
	int i;
	for(i=0;i<GM->VertexNum;i++)
	{
		GM->isTrav[i] = 0;
	}
	printf("深度优先遍历结点：");
	for(i=0;i<GM->VertexNum;i++)
	{
		if(!GM->isTrav[i])
		{
			DeepTraOne(GM,i);
		}
	}
	printf("\n");
}


void main()
{
 GraphMatrix GM;

 printf("输入生成图的类型：");
 scanf("%d",&GM.GType);
 printf("输入图的顶点数量：");
 scanf("%d",&GM.VertexNum);
 printf("输入图的边数量：");
 scanf("%d",&GM.EdgeNum);
 ClearGraph(&GM);
 CreateGraph(&GM);
 printf("改图的邻接矩阵数据如下：\n");
 OutGraph(&GM);
 DeepTraGraph(&GM);
}