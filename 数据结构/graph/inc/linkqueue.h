#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdlib.h>
typedef int qelemtype; //����Ԫ�ص�����  
			
typedef struct qnode
{
	qelemtype data;
	
	struct qnode *next;
}qnode;

typedef struct linkqueue
{
	struct qnode *first;			//ָ���ͷ��Ԫ�ؽ��
	struct qnode *last;				//ָ���β��Ԫ�ؽ��
	
	int num;						//�����е�Ԫ�ظ���
	
	/*
		...
	*/
	
}linkqueue;

linkqueue *inintqueue();//:���䲢��ʼ��һ������
void destroyqueue(linkqueue *q);//:����һ������
void clearqueue(linkqueue *q);//�����һ������ ->���һ���ն���  
int queueisempty(linkqueue *q);//:�ж�һ�������Ƿ�Ϊ�� 
int queuelength(linkqueue *q);//: ���ض�����Ԫ�صĸ����������еĳ���
int gethead(linkqueue *q,qelemtype *e);//:���ض���ͷԪ�أ��������ӡ�
int enqueue(linkqueue *q, qelemtype e);//:���
int dequeue(linkqueue *q, qelemtype *e);//:����  


#endif 