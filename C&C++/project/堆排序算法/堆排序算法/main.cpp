#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10  //数组大小

void HeapSort(int a[],int n)   //堆排序
{
	int i,j,h,k;
	int t;

	for(i=n/2-1;i>=0;i--)       //将a[0,n-1]建成大根堆
	{
		while((2*i+1) < n)          //第i个结点有右子树
		{
			j = 2*i + 1;
			if((j+1)<n)
			{
				if(a[j]<a[j+1]) //左子树小于右子树，则需要比较右子树
					j++;        //序号增加1,指向右子树
			}
			if(a[i]<a[j])     //比较i与j为序号的数据
			{
				t=a[i];       //交换数据
				a[i]=a[j];
				a[j]=t;
				i=j;      //堆被破坏，需要重新调整
			}
			else             //比较左右子节点均大则堆未破坏，不再需要调整
			{
				break;
			}
		}
	}
	//输出构成的堆
	printf("原数据构成的堆：");
	for(h=0;h<n;h++)
	{
		printf("%d ",a[h]);        //输出
	}
	printf("\n");

	for(i=n-1;i>0;i--)
	{
		t=a[0];           //与第i个记录交换
		a[0]=a[i];
		a[i]=t;
		k=0;
		while((2*k+1)<i)  //第i个结点有右子树
		{
			j=2*k+1;
			if((j+1)<i)
			{
				if(a[j]<a[j+1])       //左子树小于右子树，则需要比较右子树
				{
					j++;         //序号增加1，指向右子树
				}
			}
			if(a[k]<a[j])  //比较i与j为序号的数据
			{
				t=a[k];       //交换数据
				a[k]=a[j];
				a[j]=t;
				k=j;              //堆被破坏，需要重新调整
			}
			else            //比较左右子节点均大则未破坏，不再需要调整
			{
			   break;
			}
		}

		printf("第%d步排序结果：",n-i);   //输出每步排序的结果
		for(h=0;h<n;h++)
		{
			printf("%d ",a[h]);    //输出
		}
		printf("\n");
	}
}


void main()            //主函数
{
	int i;
	int shuzu[SIZE];          //声明数组

	srand(time(NULL));
	for(i=0;i<SIZE;i++)      //初始化数组
	{
		shuzu[i]=rand()/1000+100;
	}

	printf("排序前：\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",shuzu[i]);
	}

	printf("\n");

	HeapSort(shuzu,SIZE); //排序

	printf("排序后：\n");
	for(i=0;i<SIZE;i++)
	{
		printf("%d ",shuzu[i]);  //输出
	}
	printf("\n");
}