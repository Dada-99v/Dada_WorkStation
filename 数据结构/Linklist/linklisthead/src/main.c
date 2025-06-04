#include <stdio.h>
#include "linklisthead.h"



int main()
{
	struct linklisthead  *l = create_linklisthead(); //创建一个头结点
	int d;
	struct node *p = NULL;
	while(1)
	{
		scanf("%d",&d);
		if(d == 0)
		{
			break;
		}
		p = malloc(sizeof(struct node));
		p->data = d;
		p->next = NULL;
		add_a_node(l,p);
		
	}
	
	print_list(l);
	delete_all_x(l, 5);
	print_list(l);

	
	return 0;
}
