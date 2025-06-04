#ifndef __LINKLISTHEAD_H__
#define __LINKLISTHEAD_H__


#include <stdlib.h>
#include <stdio.h>
typedef int ElemType;  //数据元素的类型
			
//数据结点 
typedef struct node 
{	
	ElemType data;  //数据域：保存数据 
	struct node *next; //指针域：下一个结点的地址
	
}Node;

//头结点  
struct linklisthead
{
	struct node *first; //指向链表的第一个结点
	struct node *last;  //指向链表的最后一个结点 
	int nodenum;		//记录链表中结点的数目 
	/*
		...
		还可以定义其他的成员变量，看具体需求
	*/

};


struct linklisthead  *create_linklisthead();
void add_a_node(struct linklisthead *l, Node *p);
void print_list(struct linklisthead *h);
void delete_all_x(struct linklisthead *l, ElemType x);



#endif
