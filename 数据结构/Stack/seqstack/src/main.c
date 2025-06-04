#include <stdio.h>
#include "seqstack.h"

int main()
{	
	int d;
	int value = -1;
	seqstack *s = initstack(1024); //初始化一个栈
	while(1)
	{
		scanf("%d",&d);
		if(d == 0)
		{
			break;
		}
		value = push(s, &d); //入栈，把一个元素加到栈中去
		if(value == 0)
		{
			printf("push failed\n");
		}
	}
	//..此处省略一万行代码
	
	while(stackisempty(s) == 0) //判断一个栈是否为空
	{
		value = pop(s, &d);  //出栈，把栈顶元素给干掉 
		if(value == 0)
		{
			printf("pop failed\n");
		}
		printf("pop is %d\n",d);
	}
	
	clearstack(s); //清空一个栈
	destroystack(s); //销毁一个栈

	return 0;
}
