#include "linklisthead.h"


/*创建一个头结点*/
struct linklisthead  *create_linklisthead()
{
	struct linklisthead *l = malloc(sizeof(struct linklisthead));
	l ->first = NULL;
	l ->last = NULL;
	l ->nodenum = 0;

	return l;
}


/*
			add_a_node:把p指向的数据结点，添加到l指向的带头结点的
			单链表中去
			在添加p后l仍然保持升序 
			l:l指向的单链表是升序 
			p:要增加的数据结点
		*/
void add_a_node(struct linklisthead *l, Node *p)
{
	if(l == NULL || p == NULL)
	{
		return; 
	}
	if(l->first == NULL)
	{
		//空链表，l上面一个数据结点也没有
		l->first = p;
		l->last = p;
		l->nodenum++;
		return;
	}

	//1.找插入位置
	// 	pk以及pk前面的那个结点pr
	//2.插入操作	
	struct node *pk = l->first;
	struct node *pr = NULL;

	while(pk)
	{
		if(pk ->data > p->data)
		{
			break;
		}
		pr = pk;
		pk = pk ->next;
	
	}

	//两种情况
	if(pk == NULL)
	{
		l->last->next = p;
		l->last = p;
	}
	else 
	{
		if(pk == l->first)
		{
			p->next = l->first;
			l->first = p;
		}
		else 
		{
			p->next = pk;
			pr ->next = p;
		}
	}

	l->nodenum++;
		
}


/*
	打印一个链表 
*/
void print_list(struct linklisthead *h)
{	
	struct node *p = h->first;
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
	
}

/*在“带头结点的单链表”上删除结点 */
void delete_all_x(struct linklisthead *l, ElemType x)
{
	struct node *px = l->first;		//指向要删除的结点
	struct node *pr = NULL;			//指向px前面的那个结点
	struct node *ph = l->first;		//每次遍历起始结点

	while(1)
	{
		//1.先找到要删除的结点 
		px = ph;
		while(px)
		{
			if(px->data == x)
			{
				break;
			}
			pr = px;
			px = px->next;
		}
		if(px == NULL)
		{
			return;
		}
		ph = px->next;	//下一次搜索应该从px的下一个结点开始
		if(px == l->first)  //要删除的结点为第一个结点
		{
			if(l->first == l->last)
			{
				//链接表中只有一个结点，并且要删除的这个结点
				l->first = l->last = NULL;
			}
			else 
			{
				l->first = px->next;
				px->next = NULL;
			}
		}
		else if(px == l->last) //要删除的结点为最后一个结点
		{
			//链表至少有两个及以上的结点
			pr->next = NULL;
			l->last = pr;
		}
		else  //要删除的结点为中间结点
		{
			pr->next = px->next;
			px->next = NULL;
		}

		free(px);
		px = NULL;


	}

	

}





