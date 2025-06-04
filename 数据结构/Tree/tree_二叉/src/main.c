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

		binode *t = malloc(sizeof(binode));
		t->data = d;
		t->lchild = NULL; 
		t->rchild = NULL;
		root = add_a_node(root, t);
	}
	pre_order(root);  //先序遍历 
	printf("\n");
	mid_order(root);  //中序遍历 
	printf("\n");
	/*post_order(root); //后序遍历 
	printf("\n");
	level_order(root); //层次遍历 */
	root = delete_x(root,100);
	pre_order(root);  //先序遍历 
	printf("\n");
	mid_order(root);  //中序遍历 
	printf("\n");
	return 0;
}




