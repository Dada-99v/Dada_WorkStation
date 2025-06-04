#ifndef __TREE_H__
#define __TREE_H__

#include<stdio.h>
#include<stdlib.h>
#include "linkqueue.h"

#define max(a,b) ((a) > (b) ? (a):(b))

typedef int telemtype; //树中结点元素的数据类型 

typedef struct binode
{
	telemtype data;		//数据域 
	int height;			//表示当前结点的高度 默认为1
	struct binode *lchild; //保存左子结点的指针 
	struct binode *rchild; //保存右子结点的指针
	
}binode;

void pre_order(binode *root);//先序遍历
void mid_order(binode *root);//中序遍历 
void post_order(binode *root);//后序遍历
void level_order(binode *root);//层次遍历

binode * add_a_node(binode *root, telemtype x); //往平衡二叉排序树中添加结点

binode *delete_x(binode * root,telemtype x); //删除一棵二叉排序树中的结点

binode *insert(binode *root,binode *t);		//往平衡二叉树中插入结点

int h(struct binode *t);		//求一棵二叉树的高度

binode *singlerotatewithleft(binode *k);  //对k进行单向左旋

binode *singlerotatewithright(binode *k);  //对k进行单向右旋

binode *doublerotateleftright(binode *k);	//对k进行先左后右双向旋转

binode *doublerotaterightleft(binode *k);	//对k进行先右后左双向旋转


#endif
