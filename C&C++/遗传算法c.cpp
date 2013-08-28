#include<iostream>
#include<time.h>
#include <stdlib.h>
#include<cmath>
using namespace std;

const int M=8,T=2;        //  M 群体大小，pc 交叉概率,pm 变异概率,T 终止代数
const double pc=0.6,pm=0.01;

struct population        //定义群体结构
{int x[20];
 double x1,x2;
 double fit;
 double sumfit;
}p[M];

void initial(population *);                //初始化函数
void evaluefitness(population *);          // 计算适应度
void select(population *);                 // 选择复制函数
void crossover(population *);              // 交叉函数
void mutation(population *);               // 变异函数
void decoding(population *);               // 解码函数
void print(population *);                  //显示函数

int main()                                //遗传算法主函数
{int gen=0;
 initial(&p[0]);                          //随机获得初始解
 cout<<"initialed!"<<endl;
 print(&p[0]);
 decoding(&p[0]);                      //先解码
  cout<<"decoded!"<<endl;
  print(&p[0]);
  evaluefitness(&p[0]);                  //计算适应值与累计适值
  cout<<"evalued!"<<endl;
  print(&p[0]);
 while(gen<=T)
 {cout<<"gen="<<gen+1<<endl;
  select(&p[0]);
  decoding(&p[0]); 
  evaluefitness(&p[0]); 
  cout<<"selected!"<<endl;
  print(&p[0]);
  crossover(&p[0]);
  decoding(&p[0]); 
  evaluefitness(&p[0]); 
  cout<<"crossovered!"<<endl;
  print(&p[0]);
  mutation(&p[0]);
  decoding(&p[0]); 
  evaluefitness(&p[0]); 
  cout<<"mutated!"<<endl;
  print(&p[0]);
  gen++;
 }
 decoding(&p[0]);
 evaluefitness(&p[0]);
 cout<<"最后得出的满意解为:"<<endl;
 for(int i=0;i<M;i++)
	 cout<<"x1:"<<p[i].x1<<"  x2:"<<p[i].x2<<"  值: "<<p[i].fit<<endl;  
return 0;
}
/*****************************初始化函数*****************************/
int rand01()               //用于随机取0或1的函数
{int r;
 float q;
 q=rand()/(RAND_MAX+0.0);
 if(q<0.5)  r=0;
 else       r=1;
 return r;
}
 
void initial(population *t) //群体初始化函数
{int j;
 population *po;
 srand(time(0));
 for(po=t;po<t+M;po++)
   for(j=0;j<20;j++)
    (*po).x[j]=rand01();
}

/*************************计算适应值函数*********************************/
void evaluefitness(population *t)           //计算适应值函数
{double f,x1,x2,temp=0.0;
 population *po,*po2;
 for(po=t;po<t+M;po++)
 {x1=(*po).x1;
 x2=(*po).x2;
 f=100.0*(x1*x1-x2*x2)*(x1*x1-x2*x2)+(1.0-x1)*(1.0-x1);
 (*po).fit=f;
 }
 for(po=t;po<t+M;po++)                     //计算累计适应值
 {for(po2=t;po2<=po;po2++)
    temp=temp+(*po2).fit;
 (*po).sumfit=temp;
 temp=0.0;
 }
}

/**************************选择复制函数********************************/
double randab(double a,double b)        //在区间(a,b)内生成一个随机数
{double c,r;
 c=b-a;
 r=a+c*rand()/(RAND_MAX+1.0);
 return r;
}
 
void select(population *t)              //选择算子函数
{int i=0;
 population pt[M],*po;
 double s;
 srand(time(0));
 while(i<M)
 {s=randab((*t).sumfit,(*(t+M-1)).sumfit);             
  for(po=t;po<t+M;po++)
  {if((*po).sumfit>=s) {pt[i]=(*po);break;}
   else continue;
  }
  i++;
 }
 for(i=0;i<M;i++)                      //将复制后数据pt[M]转入p[M]
	 for(int j=0;j<20;j++)
		 p[i].x[j]=pt[i].x[j];
}

/***************************交叉函数*******************************/
void crossover(population *t)        //交叉算子函数
{population *po;
 double q;                      //用于存一个0到1的随机数
 int d,e,tem[20];                     //d存放从1到19的一个随机整数，用来确定交叉的位置
          //e存放从0到M的一个随机且与当前P[i]中i不同的整数，用来确定交叉的对象
 srand(time(0));
 for(po=t;po<t+M/2;po++)
 {q=rand()/(RAND_MAX+0.0);
  if(q<pc)
  {for(int j=0;j<M;j++)          //运算M次，避免产生群体中某个体与自己交叉的情况
  {e=rand()%M;                  //随机确定交叉对象
  if(t+e!=po) break;}           //不能重复
   d=1+rand()%19;               //随机确定交叉位置
   for(int i=d;i<20;i++)
   {tem[i]=(*po).x[i];
    (*po).x[i]=(*(t+e)).x[i];
	(*(t+e)).x[i]=tem[i];
   }
  }
    else continue;
 }
}
 
/***************************变异函数*******************************/
void mutation(population *t)      //变异算子函数
{double q;                     //q用来存放针对每一个基因座产生的[0，1]的随机数
 population *po;
 srand(time(0));
 for(po=t;po<t+M;po++)
 {   int i=0;
	 while(i<20)
 {q=rand()/(RAND_MAX+0.0);           
  if(q<pm) (*po).x[i]=1-(*po).x[i];
  i++;
 }
 }
}
  
/***************************解码函数*******************************/
void decoding(population *t)        //解码函数
{population *po;
 int temp,s1=0,s2=0;
 float m,n,dit;
 n=ldexp(1,10);                  //n=2^10
 dit=4.096/(n-1);                //dit=(U(max)-U(min))/n-1
 for(po=t;po<t+M;po++)
 {for(int i=0;i<10;i++)
 {temp=ldexp((*po).x[i],i);
 s1=s1+temp;}
 m=-2.048+s1*dit;
 (*po).x1=m;
 s1=0;
 for(int j=10;j<20;j++)
 {temp=ldexp((*po).x[j],j-10);
 s2=s2+temp;}
 m=-2.048+s2*dit;
 (*po).x2=m;
 s2=0;
 }
}
 
/*******************************显示函数**************************************/
void print(population *t)
{population *po;
for(po=t;po<t+M;po++)
{for(int j=0;j<20;j++)
	{cout<<(*po).x[j];
if((j+1)%5==0) cout<<"  ";}
  cout<<endl;
  cout<<(*po).x1<<"  "<<(*po).x2<<"  "<<(*po).fit<<"  "<<(*po).sumfit<<endl;
}
}