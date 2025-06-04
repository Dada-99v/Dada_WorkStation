#ifndef __SEQSTACK_H__
#define __SEQSTACK_H__
#include <stdlib.h>

typedef int selemtype; 

typedef struct seqstack
{
	//selemtype elem[stack_max_length];
	selemtype *elem;
	int top;  //栈顶的下标
	int max_len; //指向的空间最大的存放的元素个数  
}seqstack;



seqstack *initstack(int max_len); //初始化一个栈
void destroystack(seqstack *s); //销毁一个栈
void clearstack(seqstack *s); //清空一个栈
int stackisempty(seqstack *s); //判断一个栈是否为空
int stacklength(seqstack *s); //求栈的长度，元素个数
int gettop(seqstack *s,selemtype *e);  //返回栈顶元素
int pop(seqstack *s, selemtype *e);  //出栈，把栈顶元素给干掉 
int push(seqstack *s, selemtype *e); //入栈，把一个元素加到栈中去







#endif

