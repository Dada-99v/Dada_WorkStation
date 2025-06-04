#include "linkqueue.h"

/*
	inintqueue:��ʼ��һ������
	����ֵ�� 
		����һ�����е�ͷ���ĵ�ַ�����������
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
	destroyqueue:����һ������
	q:����Ҫ���ٵĶ���
*/
void destroyqueue(linkqueue *q)
{
	if(q == NULL) //���е�ͷ��㶼û��
	{
		return;
	}
	if(q ->first == NULL) //������ͷ��㵫��û�����ݽ��
	{
		free(q);
		q == NULL;
		return;
	}
	
	clearqueue(q);  //��������е����ݽ��
	
	free(q);

	return;
	
}
/*
	clearqueue:���һ������
	q����ʾҪ��յĶ���
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
	queueisempty:�ж�һ�������Ƿ�Ϊ��
	q:Ҫ�жϵ��Ǹ�����
		����ֵ 
			1 Ϊ�� 
			0 Ϊ�ǿ�
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
	queuelength:��һ����ʽ���еĳ���
	q:Ҫ�󳤶ȵĶ���
		����ֵ
			���ض��еĳ���
	
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
	enqueue:��ʾ��Ӳ��� 
	q:Ҫ��Ķ���
	����ֵ
		1 �ɹ�
		0 ʧ��
	
*/
int enqueue(linkqueue *q, qelemtype e)
{
	if(q == NULL)
	{
		return 0;
	}
	//����һ��Ҫ��ӵ����ݽ��
	qnode *p = malloc(sizeof(qnode));
	p ->data = e;
	p ->next =NULL;
	//����Ǹ��ն���
	if(q->first == NULL)
	{
		q->first = p;
		q->last = p;
	}
	else //���Ǹ��ն���
	{
		q->last->next = p;
		q->last = p;
	}
	q->num++;
	return 1;
}
/*
	dequeue:���Ӳ���
	q��Ҫ���г��ӵĶ���
	e���������Ԫ�ص�ֵ�ĵ�ַ�ռ�
		����ֵ 
			1 �ɹ�
			0 ʧ��
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
	gethead:��ȡ���е�ͷԪ��
	q:Ҫ��ȡ��ͷԪ�صĶ���
	����ֵ 
		1 �ɹ�
		0 ʧ��
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

