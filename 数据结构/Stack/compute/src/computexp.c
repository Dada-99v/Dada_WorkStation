#include"computexp.h"


/*
	expression：计算字符串表达式的值
	e:指向字符串表达式所在的空间
		返回值 
			返回计算出的字符串代表的表达式的值
			
	表达式求值：
		表达式是以字符串的形式给出的，要解析字符串： 
			分解出 操作数 运算符 

		弄两个栈： 
			操作数 栈s1
			运算符 栈s2 
		while(不停解析表达式字符串)
		{
			当前解析出的是操作数 则直接入栈 s1 push(s1)
			当解析出的是运算符 则： 
			loop:	if :运算符栈为空 || 待入栈的运算符 优先级 比栈顶运算符高，
				直接入栈 push(s2)
					break;
				else :待入栈的运算符 优先级 比栈顶元素不高  
					则需要把栈顶运算符 干掉 
						从操作数栈 s1 出栈两个操作数 a b 
						从运算符栈 s2 出栈一个运算符 op
						b op a  ->结果入栈s1	
			goto loop			
		}

		要把运算符栈中的运算符出栈
			12 + 30 * 5 + 7	
*/
int expression(char *e)
{
	seqstack *s1 = initstack(1024); //初始化一个栈  操作数 栈s1
	seqstack *s2 = initstack(1024); //初始化一个栈  运算符 栈s2

	while(*e)   //当遇到\0的时候表达式结束
	{
		//[0-9]+
		while(!is_digtal(*e)) //过掉空白符..
		{
			e++;
		}
		int d;
		int s = 0;
		while(is_digtal(*e))
		{
			d = *e - '0';  		//当前的数值为
			s = s * 10 + d;
			e++;
		}
		//操作数解析出来，保存在s1栈中 
		//对于操作数则直接入栈
		int value = push(s1, &s); 			//操作数 入栈，把一个元素加到栈中去
		if(value == 0)
		{
			printf("push failed\n");
		}
		//操作数后面可能会有多余的空白符 
		while(*e && !is_operator(*e))
		{
			e++;
		}
		if(*e == '\0')
		{
			break;
		}
		//*e就是一个操作符号
		//对于操作符来说
		//要么直接入栈
		//先把栈顶元素干掉 然后入栈
		int op = *e;  //待入栈的运算符
		while(1)   //运算符栈中可能有多个运算符比待入栈的运算符优先级不低
		{
			int op_top;
			value = gettop(s2,&op_top);  //返回栈顶元素
			if(value == 0)
			{
				printf("gettop failed\n");
			}
			if(stackisempty(s2) || compare(op,op_top))  //待入栈的运算符比栈顶的运算优先级高
			{
				//入栈  
				push(s2,&op);
				break;
			}
			else
			{
				//栈顶元素的优先级比你要不低，所以先干掉栈顶元素 
				//把运算符出栈 操作数 2个出栈
				//结果入栈  
				int a,b;
				int op_top;
				pop(s1,&b);
				pop(s1,&a);

				pop(s2,&op_top);

				printf("%d %c %d = %d\n",a,op_top,b,cal(a,b,op_top));
				int d = cal(a,b,op_top);
				push(s1,&d);	
				
			}
		
		}
		
		

	}
	
//要把运算符栈中的运算符出栈
	while(!stackisempty(s2))
	{
		int a,b;
		int op_top;
		pop(s1,&b);
		pop(s1,&a);

		pop(s2,&op_top);

		printf("%d %c %d = %d\n",a,op_top,b,cal(a,b,op_top));

		int d = cal(a,b,op_top); 
		push(s1,&d);

	}
	//最终的结果 保存在s1栈中
	int r; 
	pop(s1,&r);

	destroystack(s1); //销毁一个栈
	destroystack(s2); //销毁一个栈

	return r;
}
/*
	判断字符c是否为十进制数字字符 
	 1 表示 是数字字符 
	 0 表示 不是数字字符
*/
int is_digtal(char c)
{
	if(c >= '0' && c <= '9')
	{
		return 1;
	}
	return 0;
	
}
/*
	判断字符是否为一个操作符
	// + - * / % 
	返回 1 表示 是 操作符
	返回 0 表示 不是 操作符
*/
int is_operator(char c)
{
	if(c == '+' || c== '-' || c == '*' || c == '/' || c == '%')
	{
		return 1;
	}
	return 0;
}
/*
	如果op1的优先级高于 op2
	返回 1
	否者返回 0

*/
int compare(char op1, char op2)
{
	if((op1 == '*' || op1 == '/' || op1 == '%') && 
		(op2 == '+' || op2 == '-'))
	{
		return 1;
	}
	return 0;
}
/*
	计算出结果 
	a:操作数
	b：操作数 
	op：运算符字符
*/
int cal(int a, int b,char op)
{
	switch(op)
	{
		case '+':
				return a + b;
		case '-':
				return a - b;
		case '*':
				return a * b;
		case '/':
				return a / b;
		case '%':
				return a % b;
		default:
			printf("not support!\n");
			exit(-1);   //让程序直接死亡
	}
}





