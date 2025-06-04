#include<stdio.h>
#include"computexp.h"


int main()
{	
	char *s = "1 + 30 * 5 + 7";  
	int value = expression(s);
	printf("expression's value is %d\n",value);



	return 0;
}
