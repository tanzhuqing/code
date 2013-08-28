#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20

int main(){
	int arr[N],x,i;
	int f = -1;
	
	srand(time(NULL));
	for(i=0;i<N;i++){
	arr[i]=rand()/1000;
	}

	printf("输入要查找的整数：");
	scanf("%d",&x);

	for(i=0;i<N;i++){
		if (x == arr[i]) {
		   f=1;
		   break;
		}
	}
	printf("\n 随机生成的数据序列：\n");
	for(i=0;i<N;i++){
		printf("%d",arr[i]);
	}
	printf("\n\n");

	if(f<0)
	{
		printf("没找到数据：%d\n",x);
	}else{
		printf("数据：%d位于数组的第%d个元素处.\n",x,f+1);
	}
	system("pause");
	return 0;




}
