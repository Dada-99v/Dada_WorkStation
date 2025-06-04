#include"seqstack.h"

/*
	initstack:用来申请和初始化一个顺序栈
	max_len：栈中最多可存放多少个元素
	返回值： 
		返回一个顺序栈结构体的指针

*/
seqstack *initstack(int max_len)
{

	seqstack *s = malloc(sizeof(seqstack));
	
	s->elem = malloc(max_len * sizeof(selemtype));
	s->max_len = max_len;
	s->top = -1;
			//top 保存的栈顶元素的下标
			//top == -1时，表示栈是一个栈空(什么元素都没有)
			//top++
			//elem[top] = e;

	return s;
}
/*
	destroystack：销毁一个顺序栈
	s：要销毁的顺序栈
*/
void destroystack(seqstack *s)
{
	if(s == NULL)
	{
		return;
	}

	if(s->elem)
	{
		free(s->elem);	//存栈中的元素的空间
		s->elem = NULL;
	}
	free(s);		//表示一个栈空间
	s = NULL;
}
/*
	clearstack：清空一个顺序栈
	s：表示要清空的顺序栈

*/
void clearstack(seqstack *s)
{
	if(s)
	{
		s->top = -1;
	}
}
/*
	stackisempty：判断一个栈是否为空 
	s:表示要判断的栈
	返回值 
		1 栈空 
		0 不为空
*/
int stackisempty(seqstack *s)
{
	if(s == NULL)
	{
		return 1;
	}
	return s->top == -1 ? 1 : 0;
}


/*
	stacklength：求一个栈中的元素个数
	s:表示要求栈中元素个数的栈
	返回值： 
		返回元素的个数
*/
int stacklength(seqstack *s)
{
	if(s == NULL)
	{
		return 0;
	}
	return s->top + 1;
}
/*
	gettop：返回栈顶元素，但不出栈
	=>s可能是为NULL，
	 	-》失败     0
	gettop的设计：不仅要能够返回栈顶元素 
					并且可以指示改函数是否调用成功

	返回值 
		1 表示成功
	 	0 表示失败

*/
int gettop(seqstack *s,selemtype *e)
{
	if(s == NULL || s->top == -1 || e == NULL)
	{
		return 0;
	}
	*e = s->elem[s ->top];  //满栈

	return 1;
}
/*
	pop：出栈，把栈顶元素删除
	s:表示出栈的那个栈 
	e:出栈的元素 
		返回值 
			0 表示失败
			1 表示成功
*/
int pop(seqstack *s, selemtype *e)
{
	if(s == NULL || s->top == -1 || e == NULL)
	{
		return 0;
	}
	*e = s->elem[s->top];
	s->top--;  //出栈 

	return 1;
}
/*
	push:入栈，把一个元素加到栈中去
	s:表示要入栈的栈
	e:表示要入栈的元素
	返回值： 
		1 成功 
		0 失败
*/
int push(seqstack *s, selemtype *e)
{
	if(s == NULL || s->top == s->max_len - 1)
	{
		return 0; 
	}

	s->top++;
	s->elem[s->top] = *e;
	return 1;
}





