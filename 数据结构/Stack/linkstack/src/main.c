#include <stdio.h>
#include "linkstack.h"
int main()
{

	
	linkstack *s = initstack();
	int d = 8;
	int value =  push(s,&d);
	if(value == 0)
	{
		printf("push failed\n");
	}
	d = 9;
	value =  push(s,&d);
	if(value == 0)
	{
		printf("push failed\n");
	}
	d = 10;
	value =  push(s,&d);
	if(value == 0)
	{
		printf("push failed\n");
	}
	
	int c = 0;
	while(!stackisempty(s))
	{
		value = pop(s,&c);
		if(value == 0)
		{
			printf("pop falied\n");
		}
		printf("c = %d\n",c);
	}
	

	destroystack(s);
	
	
	
	return 0;
}
