// pso.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define P_num 20          //粒子数目 
#define dim 30
#define low -30           //搜索域范围
#define high 30
#define iter_num 600
#define V_max 20          //速度范围
#define c1 2
#define c2 2
#define w 0.5
#define alp 1double particle[P_num][dim];           //个体集合
double particle_loc_best[P_num][dim];  //每个个体局部最优向量
double particle_loc_fit[P_num];        //个体的局部最优适应度,有局部最优向量计算而来
double particle_glo_best[dim];         //全局最优向量
double gfit;                           //全局最优适应度,有全局最优向量计算而来  
double particle_v[P_num][dim];         //记录每个个体的当前代速度向量
double particle_fit[P_num];            //记录每个粒子的当前代适应度   
double fitness(double a[])
{ 
	int i;
	double sum=0.0; 
	for(i=0; i<dim; i++)  
		sum += a[i]*a[i];//  sum += 100*(a[i+1]-a[i]*a[i])*(a[i+1]-a[i]*a[i])//    
//	+(a[i]-1)*(a[i]-1);
	 return sum;
}
void initial()
{
	 int i,j;
	  for(i=0; i<P_num; i++)            //随即生成粒子
		    for(j=0; j<dim; j++)
			  {  
				   particle[i][j] = low+(high-low)*1.0*rand()/RAND_MAX;    //初始化群体 
				     particle_loc_best[i][j] = particle[i][j];               //将当前最优结果写入局部最优集合  
					  particle_v[i][j] = -V_max+2*V_max*1.0*rand()/RAND_MAX;    //速度 
			 } for(i=0; i<P_num; i++)            //计算每个粒子的适应度 
			{
				  particle_fit[i] = fitness(particle[i]); 
				   particle_loc_fit[i] = particle_fit[i];
			  }
			  gfit = particle_loc_fit[0];      //找出全局最优
			   j=0; 
			   for(i=1; i<P_num; i++)
			    { 
					 if(particle_loc_fit[i]<gfit) 
					  {  
						   gfit = particle_loc_fit[i]; 
						     j = i; 
					  }
			    } for(i=0; i<dim; i++)             //更新全局最优向量  
					  particle_glo_best[i] = particle_loc_best[j][i];
}
void renew_particle(){ 
	int i,j;
	 for(i=0; i<P_num; i++)            //更新个体位置生成位置
		   for(j=0; j<dim; j++)  { 
			     particle[i][j] +=  alp*particle_v[i][j]; 
				   if(particle[i][j] > high)  
					     particle[i][j] = high; 
				     if(particle[i][j] < low)  
						   particle[i][j] = low;
		     }
}
void renew_var(){ 
	int i, j;
	 for(i=0; i<P_num; i++)            //计算每个粒子的适应度 
	 {  
		 particle_fit[i] = fitness(particle[i]); 
		  if(particle_fit[i] < particle_loc_fit[i])      //更新个体局部最优值  
		  { 
			    particle_loc_fit[i] = particle_fit[i]; 
				  for(j=0; j<dim; j++)       // 更新局部最优向量    
					  particle_loc_best[i][j] = particle[i][j];  
		  }
	  }
	  for(i=0,j=-1; i<P_num; i++)                   //更新全局变量 
	  { 
		   if(particle_loc_fit[i]<gfit)
		     { 
				   gfit = particle_loc_fit[i];   
				   j = i;
		     }
	   }
	   if(j != -1) 
		    for(i=0; i<dim; i++)             //更新全局最优向量   
				  particle_glo_best[i] = particle_loc_best[j][i];
	    for(i=0; i<P_num; i++)    //更新个体速度 
			 for(j=0; j<dim; j++)
			   {  
				    particle_v[i][j] = w*particle_v[i][j]+c1*1.0*rand()/RAND_MAX*(particle_loc_best[i][j]-particle[i][j])+c2*1.0*rand()/RAND_MAX*(particle_glo_best[j]-particle[i][j]);
					   
					if(particle_v[i][j] > V_max)   
						 particle_v[i][j] = V_max; 
					  if(particle_v[i][j] < -V_max)
						      particle_v[i][j] = -V_max; 
			  }
}

int main(){ 
	int i=0; 
	srand((unsigned)time(NULL));
	 initial();
	  while(i < iter_num) 
	  { 
		   renew_particle(); 
		   renew_var(); 
		   printf("%lf\n", gfit); 
		   i++; 
	  }
 return 0;
}
