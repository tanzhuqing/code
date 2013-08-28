// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#define SPACE 0x20
#define ESC 0x1b
#define ANT_CHAR_EMPTY '+'
#define ANT_CHAR_FOOD 153
#define HOME_CHAR 'H'
#define FOOD_CHAR 'F'
#define FOOD_CHAR2 'f'
#define FOOD_HOME_COLOR 12
#define BLOCK_CHAR 177

#define MAX_ANT 50
#define INI_SPEED 3
#define MAXX 80
#define MAXY 23
#define MAX_FOOD 10000
#define TARGET_FOOD 200
#define MAX_SMELL 5000
#define SMELL_DROP_RATE 0.05
#define ANT_ERROR_RATE 0.02
#define ANT_EYESHOT 3
#define SMELL_GONE_SPEED 50
#define SMELL_GONE_RATE 0.05
#define TRACE_REMEMBER 50
#define MAX_BLOCK 100

#define NULL 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SMELL_TYPE_FOOD 0
#define SMELL_TYPE_HOME 1