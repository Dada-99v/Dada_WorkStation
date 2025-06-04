#include "squeue.h"
/*
	inintqueue:分配并初始化一个“循环队列”
	max_len：指定改队列中最大的元素个数
		返回值： 
			返回循环队列结构体的指针
*/
squeue *initqueue(int max_len)
{
	squeue *q = malloc(sizeof(*q));
	q->data = malloc(max_len * sizeof(qelemtype)) ;

	q->avail_len = 0;
	q->front = 0;
	q->rear = 0;
	q->max_len = max_len;

	return q;
}
/*
	destroyqueue：销毁一个队列
*/
void destroyqueue(squeue *q)
{
	if(q == NULL)
	{
		return;
	}
	if(q->data)
	{
		free(q->data);
		q->data = NULL;
	}
	q->rear = q->front = 0;
	q->max_len = 0;
	free(q);
	q = NULL;	
}
/*
	clearqueue:清空一个队列
	q:表示要清空的队列
*/
void clearqueue(squeue *q)
{
	if(q == NULL)
	{
		return; 
	}

	q->front = q ->rear = 0;
	q->avail_len = 0;

}
/*
	queueisempty:判断队列是否为空 
	q:表示要判断的队列
	返回值 
		返回 1 表示队列为空 
		返回 0 表示队列非空 
*/
int queueisempty(squeue *q)
{
	if(q == NULL || q->data == NULL)
	{
		return 1;
	}

	return (q->avail_len == 0)? 1 : 0;
}
/*
	queuelength:返回队列的长度 
	q:求长度的队列
	返回值  
		返回的数值就是队列的长度
*/
int queuelength(squeue *q)
{
	if(q == NULL || q->data == NULL)
	{
		return 0;
	}
	return q->avail_len;
}
/*
	enqueue：入队操作 
	q:要入的那个对
	e:要入队的元素
	返回值 
		1 表示成功
		0 表示失败
*/
int enqueue(squeue *q,qelemtype e)
{
	if(q == NULL || q->data == NULL || q->avail_len == q->max_len)
	{
		return 0;
	}
	q->data[q->rear] = e;
	q->rear++;
	if(q->rear == q->max_len)
	{
		q->rear = 0;
	}
	q->avail_len++;

	return 1;
	
}
/*
	dequeue:出队操作
	q:表示要出的那个队 
	e:出队元素值保存的地址
		返回值 
			1 成功
			0 失败 
*/
int dequeue(squeue *q, qelemtype *e)
{
	if(q == NULL || q->data == NULL || q->avail_len == 0)
	{
		return 0;
	}
	*e = q->data[q->front];
	q->front++;

	if(q->front == q->max_len)
	{
		q->front = 0;	
	}
	q->avail_len--;

	return 1;
}
/*
	gethead:获取队头元素
	q:表示要获取哪个队列的队头元素 
	e:保存获取到的队头元素的值的地址
	返回值 
		1 成功 
		0 失败

*/
int gethead(squeue *q,qelemtype *e)
{
	if(q == NULL || q->data == NULL || q->avail_len == 0)
	{
		return 0;
	}
	*e = q->data[q->front];
	return 1;
}






