#include "linkqueue.h"

/*
	inintqueue:初始化一个队列
	返回值： 
		返回一个队列的头结点的地址代表这个队列
*/
linkqueue *inintqueue()
{
	linkqueue *q = malloc(sizeof(linkqueue));
	q->first = NULL;
	q->last = NULL;
	q->num = 0;

	return q;
}

/*
	destroyqueue:销毁一个队列
	q:代表要销毁的队列
*/
void destroyqueue(linkqueue *q)
{
	if(q == NULL) //队列的头结点都没有
	{
		return;
	}
	if(q ->first == NULL) //队列有头结点但是没有数据结点
	{
		free(q);
		q == NULL;
		return;
	}
	
	clearqueue(q);  //清除队列中的数据结点
	
	free(q);

	return;
	
}
/*
	clearqueue:清空一个队列
	q：表示要清空的队列
*/
void clearqueue(linkqueue *q)
{
	if(q == NULL || q->first == NULL)
	{
		return;
	}

	qnode *p = q->first; 
	while(p)
	{
		q->first = p ->next;
		p->next = NULL;
		free(p);
		p = q->first;
	}
	q->last = NULL;
	q->num = 0;

	return;

}

/*
	queueisempty:判断一个队列是否为空
	q:要判断的那个队列
		返回值 
			1 为空 
			0 为非空
*/
int queueisempty(linkqueue *q)
{
	if(q == NULL || q->num == 0)
	{
		return 1;
	}
	return 0;
		
}
/*
	queuelength:求一个链式队列的长度
	q:要求长度的队列
		返回值
			返回队列的长度
	
*/
int queuelength(linkqueue *q)
{
	if(q == NULL)
	{
		return 0;
	}
	return q->num;
}
/*
	enqueue:表示入队操作 
	q:要入的队列
	返回值
		1 成功
		0 失败
	
*/
int enqueue(linkqueue *q, qelemtype e)
{
	if(q == NULL)
	{
		return 0;
	}
	//创建一个要入队的数据结点
	qnode *p = malloc(sizeof(qnode));
	p ->data = e;
	p ->next =NULL;
	//如果是个空队列
	if(q->first == NULL)
	{
		q->first = p;
		q->last = p;
	}
	else //不是个空队列
	{
		q->last->next = p;
		q->last = p;
	}
	q->num++;
	return 1;
}
/*
	dequeue:出队操作
	q：要进行出队的队列
	e：保存出队元素的值的地址空间
		返回值 
			1 成功
			0 失败
*/
int dequeue(linkqueue *q, qelemtype *e)
{
	if(q == NULL || q->num == 0)
	{
		return 0;
	}

	qnode *px = q ->first;
	q->first = px->next;
	px->next = NULL;
	if(q->first == NULL)
	{
		q->last = NULL;
	}
	
	*e = px ->data;
	free(px);
	q->num--;
	return 1;

}
/*
	gethead:获取队列的头元素
	q:要获取的头元素的队列
	返回值 
		1 成功
		0 失败
*/
int gethead(linkqueue *q,qelemtype *e)
{
	if(q == NULL || q->num == 0)
	{
		return 0;
	}
	*e = q->first->data;
	return 1;
}

