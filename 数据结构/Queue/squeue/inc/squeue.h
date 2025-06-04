#ifndef __SQUEUE_H__
#define __SQUEUE_H__

#include <stdlib.h>

typedef int qelemtype;   //队列元素的类型 
				
typedef struct squeue
{
	qelemtype *data;   //指向一段连续的存储单元
						//用来存储队列中的元素 
	int rear;			//队尾的下标，下一个入队元素的下标
	int front;			//队头下标，下一个出队元素的下标
	
	int max_len;		//表示data指向的存储空间最大的元素个数
	int avail_len;		//表示当前队列中的元素个数
	/*
		...
	*/
}squeue;  		
			

squeue *initqueue(int max_len);//:分配并初始化一个队列
void destroyqueue(squeue *q);//:销毁一个队列
void clearqueue(squeue *q);//：清空一个队列 ->变成一个空队列  
int queueisempty(squeue *q);//:判断一个队列是否为空
int queuelength(squeue *q);//: 返回队列中元素的个数，即队列的长度
int enqueue(squeue *q,qelemtype e);//:入队
int dequeue(squeue *q, qelemtype *e);//:出队 
int gethead(squeue *q,qelemtype *e);//:返回队列头元素，但不出队
#endif 