#ifndef __TREE_H__
#define __TREE_H__

#include<stdio.h>
#include<stdlib.h>
#include "linkqueue.h"

typedef int telemtype; //树中结点元素的数据类型 

typedef struct binode
{
	telemtype data;		//数据域 
	
	struct binode *lchild; //保存左子结点的指针 
	struct binode *rchild; //保存右子结点的指针
	
}binode;

void pre_order(binode *root);//先序遍历
void mid_order(binode *root);//中序遍历 
void post_order(binode *root);//后序遍历
void level_order(binode *root);//层次遍历

binode * add_a_node(binode *root, binode *t); //往二叉排序树中添加结点

binode *delete_x(binode * root,telemtype x); //删除一棵二叉排序树中的结点



#endif