#ifndef Evaluate_H_H
#define Evaluate_H_H
#include<iostream.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<conio.h>
#include"Parameter.h"
#include"BrowseDir.h"


static int m_FeedSetFileNum[2];

class CEvaluate
{

public:
       int GetFileCount();
       int WriteInfo(char *filename);
       int CopyFeature(Feature &K,const Feature X);
       int GetAccuracy();
       bool BrowseDir(const char *dir,const char *filespec);
       bool ProcessFile(const char *filename);
       bool BeginBrowse(const char *filespec);
       bool SetInitDir(const char *dir);
       CEvaluate();
       ~CEvaluate()
       {
                   delete stopwordArray;
       }
       int Classify(const char *str,int Num);
       int ShellSortKeyWords(FileNode &filenode,int N);
       int SelectFeature(Feature feature[],int Num);
       int PreDealFile(const char *filename,FileNode &filenode);
       int SeekKeyWords(FileNode Src, const char *Des, int num);
       int ShellSortAccordStr(Feature M[],int N);  //按字符串升序排列 
       
       
protected:
          bool Del_StopWord(const char *Word,int Num);
          int ReadStopList(const char *stoptext);
          int Binary(const char *Src,FileNode filenode,int N);
          int MergesortInString(Feature feature[],int Num);
          int MergeInKeyString(FileNode &filenode,KeyWord swap[], int k,int n);
          int ReadInfo();
          int merge(Item x[],Item swap[],int k,int n);
          int mergesort(char *file,int Setflag);
          int Copy(Item &K,const Item M);
          int FeedBack(const char *filename,int flag);
          int ShellSort(Item M[],int N);//按单词在文章升序排序
          int ShellSortInFreq(Item M[],int N); //按单词在文章中出现的次数降序排序
          int Seek(Item *Sour,const char *Des, int num);
          
public:
       WordReseroir WordReservoirInfo[2];
       int flag;  //指明邮件标志
       int m_nFileCount;
       int m_nAccuracy;  //记录分类正确的邮件数量
       double m_SetFileNum[2];
       
protected:
         StopWord *stopwordArray;
         int m_StopWordNum;
         int MergeInKeyWords(FileNode &filenode, int N);
         char m_MailDir[40];  //待处理的邮件路径
         char m_szInitDir[_MAX_PATH]; 
private:      
      
      
};
#endif
