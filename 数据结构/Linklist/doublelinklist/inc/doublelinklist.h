#ifndef __DOUBLELINKLIST_H__
#define __DOUBLELINKLIST_H__


#include <stdlib.h>
#include <stdio.h>
typedef int ElemType;   //数据元素的类型  
	
//数据结点  
struct binode
{
	ElemType data;   //数据域
	struct binode *next;  //指向后续结点
	struct binode *prev;  //指向前驱结点
};

//头结点  
struct bilinklisthead
{
	struct binode *first;  //指向双向链表的第一个结点
	struct binode *last;   //指向双向链表的最后一个结点。
	/*
		...
	*/

};

struct bilinklisthead *create_bilinklisthead(); //创建一个双链表的头结点
void add_a_binode(struct bilinklisthead *l,struct binode *p); //往双向链表中添加一个数据结点
void print_bilinlist(struct bilinklisthead *l); //打印一个带头结点的双向链表
void delete_all_x(struct bilinklisthead *l, ElemType x);//删除一个数据结点




#endif
