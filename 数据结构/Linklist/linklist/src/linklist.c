#include "linklist.h"
/*
	创建一个链表
*/
struct node * create_linklist()
{	
	int d;
	struct node *first = NULL; //指向新建立的链表的第一个结点
	struct node *last = NULL; //指向新建立的链表的最后一个结点
	
	struct node *p = NULL; //指向当前的那个结点
	while(1)
	{
		scanf("%d",&d); // 1 2
		if(d == 0)
		{
			break;//结束输入
		}
		//用申请一个结点的空间来保存d
		//1.创建/申请一个结点的空间来保存数据
		p = malloc(sizeof(struct node));
		p->data = d;
		p->next = NULL;

		//2.插入  
		if(first == NULL)  //第一次插入 其实就是链表是个空链表的时候 就是往空链表插入
		{					//一个结点
			first = p;
			last = p;
		}
		else
		{
			//尾插法
			//last ->next = p;
			//last = p;

			//头插法 
			//p->next = first;
			//first = p;
			
			//“插入排序”
			//(1)找插入位置  
			//“遍历链表”：找到链表中第一个值比待插入结点大的结点pk(以及pk前驱结点pr),
				//pk前面就是插入的位置
			struct node *pk = NULL; //指向链表中比p值大的那个结点
			struct node *pr = NULL; //指向pk前面的那个结点
			pk = first;
			while(pk)
			{
				if(pk ->data > p ->data)
				{
					//找到了 
					break;
				}
				pr = pk;
				pk = pk ->next;
			}
				
			/*(2)"插入操作"
			遍历后，分两种情况： 
				2.1找到pk pk != NULL   
					(1)pk 为第一个结点 pk == first 
						p比链表上所以的结点的值都要小，
						p应该加入到链表的最前面。
						“头插法”
						p->next = first;
						first = p;
					(2)pk为后面或中间的结点  
						pr为pk的前驱结点，
						p应该插入在pk的前面，pr的后面 
						p->next = pk;
						pr->next  = p;	
						
				2.2没找到pk pk == NULL 
				 链表上所有的结点的值都比p要小，
				 p应该加入到链表的末尾。 
				 “尾插法”
				 last->next = p;
				 last = p;
				*/
				//插入操作
			if(pk == NULL)
			{
				//没找到 
				last ->next = p;
				last = p;
			}
			else 
			{
				if(pk == first)
				{
					p->next = first;
					first = p;
				}
				else
				{
					p->next = pk;
					pr->next  = p;
				}
			}
		}
	}
	
	return first;
	
}

/*
	打印一个链表 
*/
void print_list(struct node *h)
{	
	struct node *p = h;
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
	
}



/*把p指向结点，加入到h指向的链表中去，
	h：指向一个升序的链表 
	p：指向待插入的结点
	返回值： 
		返回插入p后，新的链表的第一个结点的指针*/
struct node *add_a_node(struct node *h, struct node *p)
{
	if(h == NULL)	//链表可能为空
	{
		return p;
	}
	if(p == NULL) //待插入的结点可能为空
	{
		return h;
	}
	
	//把p插入到h指向的链表中去。“插入”
	//1.找插入位置 
	//一个一个地遍历(从第一个开始找，找到其值比p大的那个结点pk以及pk前驱
	//结点pr)
	//pk的前面就是插入位置
	struct node *pk = NULL; //pk指向链表中第一个比p值大的结点
	struct node *pr = NULL; //pr指向pk前面的那个结点 
	pk = h; 
	while(pk)
	{
		if(pk ->data > p->data)
		{
			break;
		}
		else //pk->data <= p->data 
		{
			pr = pk;
			pk = pk ->next;
		}
	}
		
	//2.插入操作   
		/*前面找位置的结果，只有两种情况： 
			2.1没找到 pk == NULL 
				h指向的链表中所有的结点的值都比p要小 
				p应该加入到h指向的末尾“尾插法”
				此时，pr正好指向的最后那个结点  
				pr->next = p;
				
			2.2找到了 
				又分两种情况: 
					pk为第一个结点： pk == h 
						h指向的链表中的所有的结点的值都比p要大，
						p应该加入到h的前面。“头插法”
							p->next = h;
							h = p;
	
					pk为中间结点： 
						p->next = pk 
						pr ->next = p;
	
	*/
	if(pk == NULL)
	{
		pr->next = p;
	}
	else 
	{
		if(pk == h)
		{
			p->next = h;
			h = p;
		}
		else 
		{
			p->next = pk; 
			pr ->next = p;
		}
	}
	
	return h;
}


struct node *create_linklist_v2()
{
	int d;
	struct node *first = NULL; //指向新建立的链表的第一个结点
	
	struct node *p = NULL; //指向当前的那个结点
	while(1)
	{
		scanf("%d",&d); // 1 2
		if(d == 0)
		{
			break;//结束输入
		}
		//用申请一个结点的空间来保存d
		//1.创建/申请一个结点的空间来保存数据
		p = malloc(sizeof(struct node));
		p->data = d;
		p->next = NULL;

		//2.把p加入到first指向的链表中去 
		first = add_a_node(first, p);
	}

	return first;	
}


/*
delete_x:在h指向的单链表中，删除值为x的结点(假设顶多只有一个结点的值为x)
	h:指向链表(不一定有序)
	x:要删除的结点的元素值 
		返回值： 
			返回删除后的链表的第一个结点的指针 
		
*/
struct node *delete_x(struct node *h, ElemType x) //ElemType x <= > int x
{	
	struct node *px = NULL; //指向要删除的那个结点
	struct node *pr = NULL; //指向px前面的那个结点
	struct node *ph = h; 	//每次遍历的第一个(起点)结点
	if(h == NULL)
		{
			return NULL;
		}

	while(1)
	{
		//删除算法： 
		//1.先找到要删除的结点
		//遍历算法： 
		//从链表的第一个结点开始，一个一个找，
		//找到其值为x的结点px(以及px前面 那个d结点pr
	
		px = ph;
		while(px)
		{
			if(px ->data == x)
			{
				break;
			}
			pr = px;
			px = px ->next;
		}
		//2.删除 
		//(1)先摘下来
		//(2)删除free 

		//找完px后，分两种情况： 
		if(px == NULL)
		{
			return h;
		}
		ph = px->next;
		//找到了： 
			//(1)是第一个结点
			//(2)中间结点
			//(3)最后一个结点  同(2)操作一样
		if(px == h)
		{
			h = h ->next; 
			px->next = NULL;
			
		}
		else
		{
			pr->next = px ->next;
			px ->next = NULL;
			
		}
		free(px);
		
		px = NULL;
	}
	
		
	return h;	

		
}





