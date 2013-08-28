#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void kuaisu(char *a,int left,int right)
{
	int f,l,r,t;
	l=left;
	r=right;
	f=a[(left+right)/2];

	while(l<r)
	{
		while(a[l]<f)  ++l;
		while(a[r]<f)  --r;

		if(l<=r)
		{
			t=a[l];
			a[l]=a[r];
			a[r]=t;
			++l;--r;
		}
	}
	if(l == r)
		l++;
	if(left < r)
	{
		kuaisu(a,left,l-1);   //µÝ¹éµ÷ÓÃ
	}
	if(l<right)
	{
		kuaisu(a,r+1,right);  //µÝ¹éµ÷ÓÃ
	}
}

int mian()
{
	char str[80];
	int N;

	memset(str,'\0',sizeof(str));

	printf("ÊäÈëÒ»¸ö×Ö·û´®:");
	scanf("%s",str);   //ÊäÈë×Ö·û´®

	N=strlen(str);

	printf("ÅÅÐòÇ°£º\n");
	printf("%s\n",str);   //Êä³ö

	kuaisu(str,0,N-1);   //ÅÅÐò

	printf("ÅÅÐòºó£º\n");
	printf("%s\n",str);  //Êä³ö

	system("pause");

	return 0;
}