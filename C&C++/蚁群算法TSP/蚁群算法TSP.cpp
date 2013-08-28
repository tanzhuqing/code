// 蚁群算法TSP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<time.h>
#include <stdlib.h>
#include<cmath>
#include <tchar.h>
using namespace std;

const int N_CITY_COUNT=51; //城市数量
const int N_ANT_COUNT=20; //蚂蚁数量
const int N_IT_COUNT=10000; //迭代次数

//蚁群算法参数
const double ALPHA=1.0;
const double BETA=2.0;
const double ROU=0.98; //信息素残留系数，(1-ROU)就是信息素的挥发速度
const double Pbest=0.05; //蚂蚁一次搜索找到最优路径的概率

const double DBQ=100.0; //总的信息素
const double DB_MAX=10e9; //一个标志数
double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间信息素
double g_Distance[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间距离

double g_Prob[N_CITY_COUNT][N_CITY_COUNT];
double g_DistanceBeta[N_CITY_COUNT][N_CITY_COUNT];

int rnd(int nLow,int nUpper); //返回随机数
double rnd(double dbLow,double dbUpper);
double ROUND(double dbA);

double x_Ary[N_CITY_COUNT];
double y_Ary[N_CITY_COUNT];

struct ant
{
    int m_nPath[N_CITY_COUNT]; //蚂蚁走的路径
	double m_dbPathLength; //蚂蚁走过的路径长度

	int m_nAllowedCity[N_CITY_COUNT]; //没去过的城市
	int m_nCurCityNo; //当前所在城市编号
	int m_nMovedCityCount; //已经去过的城市数量

	bool m_blGreedSearch; //是否使用贪心原则选择下一城市
}a[N_ANT_COUNT];

struct tsp{
    ant m_cAntAry[N_ANT_COUNT];
	ant m_cBestAnt; //保存结果
	double m_dbRate; //最大信息素和最小信息素的比值

}T;

    int ChooseNextCity(); //选择下一个城市
	int GreedChooseNextCity(); //贪心原则选择下一个城市

	void ant_Init(); //初始化
	void ant_Move(); //蚂蚁在城市间移动
	void ant_Search(); //搜索路径
	void CalPathLength(); //计算蚂蚁走过的路径长度
	void tsp_InitData(); //初始化数据
	void tsp_Search(); //开始搜索
	void tsp_UpdateTrial();//更新环境信息素


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
//eil51.tsp城市坐标数据
double  x_Ary[N_CITY_COUNT]=
{
	37,49,52,20,40,21,17,31,52,51,
	42,31,5,12,36,52,27,17,13,57,
	62,42,16,8,7,27,30,43,58,58,
	37,38,46,61,62,63,32,45,59,5,
	10,21,5,30,39,32,25,25,48,56,
	30
};

double y_Ary[N_CITY_COUNT]=
{
	52,49,64,26,30,47,63,62,33,21,
	41,32,25,42,16,41,23,33,13,58,
	42,57,57,52,38,68,48,67,48,27,
	69,46,10,33,63,69,22,35,15,6,
	17,10,64,15,10,39,32,55,28,37,
	40
};
int rnd(int nLow,int nUpper)
{
	
	return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);

}

double rnd(double dbLow,double dbUpper)
{
	double dbTemp=rand()/((double)RAND_MAX+1.0);
	return dbLow+dbTemp*(dbUpper-dbLow);
}

//返回浮点数四舍五入取整后的浮点数
double ROUND(double dbA)
{
	return (double)((int)(dbA+0.5));
}

void ant_Init()
{
	for(int i=0;i<N_CITY_COUNT;i++)
	{
	  m_nAllowedCity[i]=1;//设置全部城市为没有去过
	  m_nPath[i]=0;//蚂蚁走的路径全部设置为0
	}
	m_dbPathLength=0.0;//蚂蚁走过的路径长度设置为0
	m_nCurCityNo=rnd(0,N_CITY_COUNT);	//随机选择一个出发城市
	m_nPath[0]=m_nCurCityNo;	//设置出发城市
	m_nAllowedCity[m_nCurCityNo]=0;//标识出发城市为已经去过了
	m_nMovedCityCount=1;//已经去过的城市数量设置为1
	m_blGreedSearch=false;//不使用贪心原则选择下一城市
}

int GreedChooseNextCity()
{
  int nSelectedCity=-1;//返回结果，先暂时把其设置为-1
  double dbLen=DB_MAX;
  for (int i=0;i<N_CITY_COUNT;i++)
  {
    if(m_nAllowedCity[i]==1)//选择没去过的城市
	{
	   if(g_Distance[m_nCurCItyNo][i]<dbLen)
	   {
		   dbLen=g_Distance[m_nCurCityNo][i];
		   nSelectedCity=i;
	   }
	
	}
  
  }
  return nSelectedCity;
}
int ChooseNextCity()
{
	intnSelectedCity=-1;//返回结果，先暂时把其设置为-1
	double dbTotal=0.0;
	double prob[N_CITY_COUNT];//保存城市被选中的概率
	for(int i=0;i<N_CITY_COUNT;i++)
	{
		if(m_nAllowedCity[i] == 1)
		{
		prob[i]=g_Prob[m_nCurCityNo][i];
		dbTotal=dbTotal+prob[i];//累加信息素，得到总和
		}
		else
			prob[i]=0.0;

	}

	double dbTemp=0.0;
	if(dbTotal>0.0)//总的信息素值大于0
	{
	    dbTemp=rnd(0.0,dbTotal);//取一个随机数
	    for(int i=0;i<N_CITY_COUNT;i++)
		{
		   if(m_nAllowedCity[i]==1)//城市没去过
		   {
			   dbTemp=dbTemp-prob[i];
			   if(dbTemp<0.0)
			   {
			     nSelectCity=i;
				 break;
			   }
		   }
		}
	
	}


	if(nSelectedCity==-1)
	{
		 for(int i=0;i<N_CITY_COUNT;i++)
		 {
			   if(m_nAllowedCity[i]==1)
			   {
				 nSelectedCity=i;
				 break;
		       } 
		 }
	}

	return nSelectedCity;
	
}


void ant_Move()
{
	int nCityNo=0;
	if(m_blGreedSearch ==true)
		nCityNo=GreedChooseNextCity();
	else
		nCityNo=ChooseNextCity();

	m_nPath[m_nMovedCityCount]=nCityNo;//蚂蚁走的路径
	m_nAllowedCity[nCityNo]=0;//没去过的城市
	m_nCurCityNo=nCItyNo;//当前所在城市的编号
	m_nMovedCityCount++;//已经去过的城市数量
}

void ant_Search()
{
	ant_Init();

	while(m_nMovedCityCount<N_CITY_COUNT)
	{
	  ant_Move();
	}

	CalPathLength();


}

void CalPathLength() //计算蚂蚁走过的路径长度
{
  m_dbPathLength=0.0;
  int m=0;
  int n=0;
  for(int i=1;i<N_CITY_COUNT;i++)
  {
     m=m_nPath[i];
	 n=m_nPath[i-1];
	 m_dbPathLength=m_dbPathLength+g_Distance[m][n];  
  }
  //加上从最后城市返回出发城市的距离
  n=m_nPath[0];
  m_dbPathLength=m_dbPathLength + g_Distance[m][n];

}


void tsp_InitData()
{
	//计算两两城市之间的距离
	double dbTemp=0.0;
	for(int i=0;i<N_CITY_COUNT;j++)
	{
	     for(int j=0;j<N_CITY_COUNT;j++)
		 {
		    dbTemp=(x_Ary[i]-x_Ary[j])*(x_Ary[i]-x_Ary[j])+(y_Ary[i]-y_Ary[j])*(y_Ary[i]-y_Ary[j]);
			dbTemp=pow(dbTemp,0.5);
			g_Distance[i][j]ROUND(dbTemp);
			g_DistanceBeat[i][j]=pow(1.0/g_Distance[i][j],BETA);
		 }
	}
	//用贪心算法生成最开始的解
	m_cBestAnt
  


}












