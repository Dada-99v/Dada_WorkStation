#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdlib.h>
typedef int qelemtype; //队列元素的类型  
			
typedef struct qnode
{
	qelemtype data;
	
	struct qnode *next;
}qnode;

typedef struct linkqueue
{
	struct qnode *first;			//指向队头的元素结点
	struct qnode *last;				//指向队尾的元素结点
	
	int num;						//队列中的元素个数
	
	/*
		...
	*/
	
}linkqueue;

linkqueue *inintqueue();//:分配并初始化一个队列
void destroyqueue(linkqueue *q);//:销毁一个队列
void clearqueue(linkqueue *q);//：清空一个队列 ->变成一个空队列  
int queueisempty(linkqueue *q);//:判断一个队列是否为空 
int queuelength(linkqueue *q);//: 返回队列中元素的个数，即队列的长度
int gethead(linkqueue *q,qelemtype *e);//:返回队列头元素，但不出队。
int enqueue(linkqueue *q, qelemtype e);//:入队
int dequeue(linkqueue *q, qelemtype *e);//:出队  


#endif 