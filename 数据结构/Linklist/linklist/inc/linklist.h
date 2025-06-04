#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;

struct node 
{
	ElemType data;  //保存数据元素 “数据域”
	struct node *next; //保存下一个数据元素的地址
};

struct node * create_linklist();  //创建一个链表
void print_list(struct node *h);		//打印链表
struct node *add_a_node(struct node *h, struct node *p); //增加一个结点
struct node *create_linklist_v2(); //创建一个链表
struct node *delete_x(struct node *h, ElemType x); //删除链表中的一个结点


#endif







