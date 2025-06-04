#include<stdio.h>
#include"tree.h"

int main()
{	
	int d;
	binode * root = NULL;
	while(1)
	{
		scanf("%d",&d);
		if(d == 0)
		{
			break;
		}
		root = add_a_node(root, d);
	}
	pre_order(root);  //先序遍历 
	printf("\n");
	mid_order(root);  //中序遍历 
	printf("\n");
	
	return 0;
}




