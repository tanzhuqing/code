#ifndef BrowseDir_H_H
#define BrowseDir_H_H
#include<iostream>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<conio.h>
#include<windows.h>
#include"Parameter.h"
using namespace std;
class CBrowseDir
{
      protected:
                //存放初始目录的绝对路径，以‘\’结尾
                char m_szInitDir[_MAX_PATH];
                int m_nFileCount;  //保存文件个数
                int m_nSubdirCount;  //保存子目录个数
      public:
             int GetSignal();
             bool Del_StopWord(const char *Word, int Num);
             int PreDeal(const char *filename, Item M[],int Num, char *Outfilename = NULL);
             void ExtractFeature(const char *filename, const char *output);  //该函数返回 指向存储特征点的文件指针
             int CalculateGain(const char *str, Feature feature[], int Num, const char *Output);
             int WriteInfo(char *filename = NULL);
             int CharDeal(char ch);
             int Copy(Item &k,const Item M);
             int merge(Item x[],Item swap[], int k, int n);
             int mergesort(char *file = NULL);
             int ShellSort(Item M[],int N);
             int Seek(Item *Sour,const char *Des,int num);
             int Split(const char *path,char *outFile,Item M[],int num);
             int ReadStopList(const char *stoptext);
             CBrowseDir();
             
             //设置初始目录为dir，如果返回false,表示目录不可用
             bool SetInitDir(const char *dir);
             
             //开始遍历初始目录及其子目录下由filespec指定类型的文件 
             //filespec可以使用通配符*？,不能包含路径
             //如果返回false,表示便利过程被用户中止
             
             bool BeginBrowse(const char *filespec);
      
      protected:
                int ShellSortInFreq(Item M[],int N);
                int MergesortInString(Feature feature[], int Num);
                int MergeInString(Feature x[],Feature swap[],int k,int n);
                int CopyFeature(Feature &K,const Feature X);
                int ShellSort(Feature M[],int N);
                int Unique(Item X[],int Num);
                int Mergesort(Feature feature[],int Num);
                int MergeInGain(Feature X[],Feature swap[],int k, int n);
                //遍历目录dir下由filespec指定的文件
                //对于子目录，采用迭代的方法
                //如果返回false，表示中止遍历文件
                bool BrowseDir(const char *dir,const char *filespec);
                
                //函数BrowseDir没找到一个文件，就调用ProcessFile
                //并把文件名作为参数传递过去
                //如果返回false,表示中止遍历文件
                //用户可以覆盖该函数，加入自己的处理代码 
                
                virtual bool ProcessFile(const char *filename);
                //函数BrowseDir每进入一个目录，就调用ProcessDir
                //并把正在处理的目录名及上一级目录名作为参数传递过去
                // 如果正在处理的是初始目录，则parentdir=NULL
                //用户可以覆盖写该函数，加入自己的处理代码
                //比如用户可以在这里统计子目录的个数
                
                virtual void ProcessDir(const char *currentdir,const char *parentdir);
                
       public:
              StopWord *stopwordArray;
              char FName[_MAX_PATH];      //存储统计后的文件存放路径
              int WordofUnique;
              int WordNumber;
              char tempFName[25];       //临时存储文件名
              bool InfoLessWord(const char *);    //初步滤掉信息量较小的单词
              int m_switch;
              int m_StopWordNum;
              char RestoreFileName[200];   //存储词库名称
              char Restore[20];    //存放文件存储目录
              //返回文件个数
              
       public：
              int GetFileCount()
              {
                  return m_nFileCount;
              }
              
              //返回子目录个数
              
              int GetSubdirCount()
              {
                 //因为进入初始目录时，也会调用函数ProcessDir,
                 //所以减1后才是真正的子目录个数
                 return m_nSubdirCount - 1;    
              } 
              
              ~CBrowseDir()
              {
                           delete stopwordArray;
              }
       private:
               WordReservoir WordReservoirInfo[2];
         
                
              
                 
                
      
      
      };
      
      //检查目录是否存在
      
      bool DirExist(const char *pszDirName);
      
      //创建目录，包含子目录，可以创建多级子目录
      
      bool CreateDir(const char *pszDirName);
      
     #endif 
