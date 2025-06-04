#include <stdio.h>
#include "linkqueue.h"

int main()
{
	linkqueue *q = inintqueue();//:分配并初始化一个队列
	int value = enqueue(q, 10); //入队
	if(value == 0)
	{
		printf("enqueue failed\n");
	}
	int d = 0;
	value = dequeue(q,&d);//:出队 
	if(value == 0)
	{
		printf("dequeue failed\n");
	} 
	printf("dequeue's is %d\n",d);

	destroyqueue(q);//:销毁一个队列

	return 0;
}
