#include<stdio.h>

long fact(int n);

void main()
{
	int i;
	printf("请输入要求阶乘的一个整数：");
	scanf("%d",&i);
	printf("%d的阶乘结果为：%ld\n",i,fact(i));            //n=32时溢出
}

long fact(int n)
{
	if(n<=1)
		 return 1;
	else return n*fact(n-1);
}