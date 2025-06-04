#include <stdio.h>
#include "doublelinklist.h"

int main()
{	
	//1.创建一个双向链表的头结点
	struct bilinklisthead *l = create_bilinklisthead();
	//2.往双向链表中插入或添加数据结点
	int d;
	while(1)
	{
		scanf("%d",&d);
		if(d == 0)		//表示用户输入结束
		{
			break;
		}
		struct binode *p = malloc(sizeof(struct binode)); //申请一个数据结点的空间并且让p指向这个空间
		p->data = d;
		p->next = NULL;
		p->prev = NULL;
		add_a_binode(l,p);
		
	}

	//3.打印双向链表里面的值
	 print_bilinlist(l);
	//4.删除结点值为x的数据结点
	delete_all_x(l, 5);
	//5.打印除双向链表里面的值
	 print_bilinlist(l);
	
	





	return 0;
}
