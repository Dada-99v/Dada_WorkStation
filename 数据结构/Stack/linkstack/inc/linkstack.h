#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__
#include <stdlib.h>
typedef int selemtype; //栈中元素的类型 
				
typedef struct node 
{
	selemtype data;
	struct node *next;

}node;

typedef struct linkstack 
{
	struct node *bottom; //栈底元素指针，链表中的第一个结点
	struct node *top;	 //栈顶元素指针，链表中的最后一个结点 
	int num;  //栈中元素个数 
	/*
		...
	*/
}linkstack;



linkstack *initstack(); //初始化一个栈 
void destroystack(linkstack *s); //销毁一个栈
void clearstack(linkstack *s); //清空一个栈 
int stackisempty(linkstack *s); //判断一个栈是否为空 
int stacklength(linkstack *s); //返回栈中的元素个数，即栈的长度
int gettop(linkstack *s,selemtype *e);  //返回栈顶元素，但不出栈

int pop(linkstack *s,selemtype *e); //出栈，把栈顶元素给干掉 
int push(linkstack *s,selemtype *e); //入栈，把一个元素加入到栈中去 



#endif 