#include<stdio.h>

int Fibonacci(int n)
{
	int t1,t2;

	if(n == 1 || n == 2)
	{
		return 1;
	}
	else {
		t1 = Fibonacci(n-1);
		t2 = Fibonacci(n-2);
		return t1+t2;
	}
}

void main()
{
	int n,num;

	printf("递推算法求解兔子产仔问题！\n");
	printf("请先输入时间：");
	scanf("%d",&n);
	num = Fibonacci(n);
	printf("经过%d月的时间，共能繁殖成%d对兔子！\n",n,num);
}