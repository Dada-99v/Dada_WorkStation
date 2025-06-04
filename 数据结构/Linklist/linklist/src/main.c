#include <stdio.h>
#include "linklist.h"

int main()
{
	
	struct node *l = create_linklist_v2();  //创建一个链表
	print_list(l);
	
	l = delete_x(l,2);
	
	print_list(l);
	
	
	return 0;
}



