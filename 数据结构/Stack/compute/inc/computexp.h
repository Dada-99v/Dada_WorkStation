#ifndef __COMPUTEXP_H__
#define __COMPUTEXP_H__

#include"seqstack.h"
#include <stdio.h>

int is_digtal(char c);   //判断字符c是否为十进制数字字符
int is_operator(char c);	//判断字符c是否为运算符
int compare(char op1, char op2); //判断2个运算符的优先级
int cal(int a, int b,char op);  //将两个变量进行运算

int expression(char *e);   //计算字符串表达式的值




#endif