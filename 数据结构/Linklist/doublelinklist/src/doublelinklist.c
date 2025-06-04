#include "doublelinklist.h"


//(1)创建一个双向链表:创建一个头结点  
struct bilinklisthead *create_bilinklisthead()
{
	struct bilinklisthead *l = malloc(sizeof(struct bilinklisthead));
	l->first = NULL; 
	l->last = NULL;

	return l;	
}

//(2)往双向链表上添加一个数据结点 
/*
	add_a_binode：在l指向的带头结点的双向链表中，
	添加一个数据结点
	l:指向一个升序的双向链表，添加p后仍然升序 
	p:待添加的数据结点
*/
void add_a_binode(struct bilinklisthead *l,struct binode *p)
{
	if(l == NULL || p == NULL)
	{
		return;
	}
	struct binode *pk = NULL; //指向链表中第一个比p值大的结点
								//前面就是p要插入的位置 		

	//插入算法： 
	//1.找插入位置 :遍历算法
	pk = l->first;  //pk指向双向链表中的第一个数据结点
	while(pk)
	{
		if(pk->data > p ->data)  //找到了第一个比p值大的结点
		{
			break;
		}
		pk = pk->next;

	}
	//2.插入操作
	if(pk == NULL)
	{
		//没找到。链表上所有的结点的值，都比p要小，或者是一个空链表
		if(l->first == NULL)
		{
			p->next = NULL;
			p->prev = NULL;

			l->first = p;
			l->last = p;
		}
		else
		{
			//不是空链表，p应该加在链表的末尾
			l->last->next = p;
			p->prev = l->last;
			l->last = p;
			p->next = NULL;
		}
	}

	else
	{
		//pk指向了一个结点，p"头插法"
		if(pk == l->first)
		{
			p->next = pk;
			pk->prev = p;
			p->prev = NULL;
			l->first = p;
		}


		else//pk可能在中间
		{
			p->next = pk;
			p->prev = pk ->prev;

			pk->prev->next = p;

			pk->prev = p;
		}

	}
	
}
/*打印一个带头结点的双向链表*/
void print_bilinlist(struct bilinklisthead *l)
{
	if(l == NULL)
	{
		return;
	}
	struct binode *p = l->first;
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}

	/*p = l->last; 
	while(p)
	{
		printf("%d ", p->data);
		p = p->prev;
	}*/
	printf("\n");
}

/*
	从双向链表中删除一个数据结点
	l:链表的头结点
	x:要删除的结点的值为x
*/
void delete_all_x(struct bilinklisthead *l, ElemType x)
{
	if(l == NULL || l->first == NULL)
	{
		return; 
	}
	struct binode *px = NULL; //指向要删除的结点；
	struct binode *ph = l->first; //遍历的起始点
	while(1)
	{
		//1.找到要删除的那个结点
		//遍历算法
		px = ph;
		while(px)
		{
			if(px->data == x)
			{
				break;
			}
			px = px ->next;
		}
		if(px == NULL)
		{
			//链表上没有值为x的结点啦 
			return;
		}
		ph = px->next;    //下一次遍历应该从px的下一个结点开始
		
		//2.删除操作 ：(1)先从原链表上摘除 (2)free  
			//第一个结点 
		if(px == l->first)
		{
			if(l->first == l->last)  //双向链表里面只有一个结点的情况
			{
				l->first = l->last = NULL;
			}
			else 
			{
				l->first = px->next;
				px->next->prev = NULL;
				px ->next = NULL;
			}
		}	
			//最后一个结点
		else if(px == l->last)
		{
			l->last = px->prev;
			px->prev->next = NULL;
			px->prev = NULL;
		}
			//中间结点 

		else
		{
			px->prev->next = px ->next;
			px ->next->prev = px->prev;
			px->next = NULL;
			px ->prev = NULL;
		}
	free(px);
	px = NULL;	
		
	}
	

}













