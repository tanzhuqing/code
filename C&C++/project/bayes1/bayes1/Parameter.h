#ifndef Paramter_H_H
#define Paramter_H_H
#include<iostream>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<conio.h>

//下面的结构用在BrowseDir类中

typedef struct Item       // 存储每个单词的信息
{
        char str[40];
        int freq;        //在某篇文章中出现的次序
        float density;
        int Sequence;   //文章编号
        int FileCnt;     //在多少篇文章中出现的次数
        int flag;
        int SetInfo;    //标记类别信息
        double gain;    //单词的增益 
} Item;

typedef struct WordGain    //将正常邮件和垃圾邮件的词库合并后，用于存储单词信息
{
        char str[40];
        
        int flag0;           //flag0表示该单词在垃圾邮件中出现 
        int freq0;
        int density0;       
        int FileCnt0;   //在多少封垃圾邮件中出现
        
        int flag1;          //flag1表示该单词的正常邮件中出现 
        int freq1;
        int density1;
        int FileCnt1;    //在多少封正常邮件中出现
        
        double qain;   //单词的增益 
         
        
}WordGain;

typedef struct WordReservoir   //词库信息数据类型
{
        char ClassFileName[100];  //存储词库的完全路径和名称
        int ClassFlag;  //词库的类别 1 表示由正常邮件提取的词库
                                   // 0 表示垃圾邮件提取的词库 
        int FileSum;     //该类文件的总数量
        int WordSum;     //该类别的单词的数量 
}Wordreservoir;

typedef struct Feature     //存储特征点信息数据结构
{
         char str[40];
         int NormalMail;
         int UnNormalMail;
         double NormalMail_Prior;
         double UnNormalMail_Proir;
         double gain;        
}Feature;

static int ClassCnt = 0;

//下面的结构用在Evaluate类中

typedef struct KeyWord   //存储关键词
{
        char str[40];
        
}KeyWord,StopWord;

typedef struct FileName   //存储文章信息包括文件名，关键词列表，和最后的分类信息
{
        char filename[40];   //文件名
        KeyWord keys[1200];   //关键词列表
        int flag;        //最后的分类信息 
}FileNode; 
 
 static int TsetKeyWordNumber = 200;  //分类时候特征数目初始化
 static int EObjectCnt = 0;     //用在Evaluate类的构造函数里面，对象计数
 
 static char Path[30] = "E:\\ReadDir\\";
 
 #define KeyNum 30    //每封邮件中提取KeyNum个单词出来，参与特征计算，对于邮件判断的准确率影响比较大
 
 #endif 
 
         
