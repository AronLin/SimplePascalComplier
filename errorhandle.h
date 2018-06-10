// Author: lin127626
// license : IBM
// reference: https://www.ibm.com/developerworks/cn/linux/l-flexbison.html
// Created by lin127626 on 2018/6/7.

/* 目的是将错误输出变得用户友好
 * 存储词法分析和语法分析的位置,分析出错误时，就能输出这个位置
 */
#ifndef ERRORHANDLE_H
#define ERRORHANDLE_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include "AbstractTree.h"
#include "parser.hpp"

extern FILE* file;
extern int ParseError;
extern YYLTYPE yylloc;
extern void init_error_handle(void);
extern void close_error_handle(void);
extern void PrintRow(void); 
extern int GetNextChar(char *b, int maxBuffer);
extern void BeginToken(char*);
extern void PrintError(char const *s, ...);


#endif //ERRORHANDLE_H
