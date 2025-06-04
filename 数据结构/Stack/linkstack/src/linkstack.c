#include "linkstack.h"
/*
	initstack:初始化一个栈
*/
linkstack *initstack() 
{
	linkstack *s = malloc(sizeof(*s));
	s->bottom = s->top = NULL;
	s->num = 0;

	return s;
}
/*
	destroystack:销毁栈
	s:表示要销毁的那个栈
*/
void destroystack(linkstack *s)
{
	if(s == NULL)
	{
		return;
	}
	//释放一个带头结点的单链表的操作
		//1.把数据结点一个一个摘下来
		//2.free
	clearstack(s);
	
	free(s);
	s = NULL;

}
/*
	clearstack:清空一个栈
	s:表示链式栈
*/
void clearstack(linkstack *s)
{
	if(s == NULL || s->bottom == NULL)
	{
		return;
	}
	node *p = s->bottom;
	while(p)
	{
		s->bottom = p->next;
		p->next = NULL;

		free(p);
		p = s ->bottom;
	}
	s->top = NULL;
	s->num = 0;
	
}
/*
	stackisempty:判断一个栈是否为空
	s:表示要判断的栈
*/
int stackisempty(linkstack *s)
{
	if(s == NULL || s->num == 0)
	{
		return 1;
	}
	return 0;
}
/*
	stacklength:求栈的长度即元素个数
	s:表示要求长度的栈
*/
int stacklength(linkstack *s)
{
	if(stackisempty(s))
	{
		return 0;
	}
	return s->num;
}
/*
	gettop:获取栈顶元素值 
	s:从哪个栈获取栈顶元素
	e:获取的元素值保存在e指向的空间中
		返回值： 
			1 成功 
				栈顶元素值保存在e指向的空间中

			0 失败
*/
int gettop(linkstack *s,selemtype *e)
{
	if(stackisempty(s))
	{
		return 0;
	}
	*e = s->top->data;

	return 1;
}
/*
	pop:出栈
	s:要出栈的那个栈
	e：出栈元素值保存在e指向的空间中
		返回值： 
			1 成功
				栈顶元素值保存在e指向的空间中
			0 失败
*/
int pop(linkstack *s,selemtype *e)
{
	if(stacklength(s) == 0)
	{
		return 0;
	}
	*e = s->top->data;
	//删除栈顶的那个结点 
	if(s->num == 1)		//如果栈中只有一个元素
	{
		s->bottom = NULL;
		free(s->top);
		s->top = NULL;
	}
	else
	{
		node *pr = s ->bottom;  //指向栈顶元素的前面那一个 
		while(pr && pr ->next != s->top)  //找栈顶元素的前一个元素
		{
			pr = pr ->next;
			
		}
		pr->next = NULL;							//出栈
		free(s->top);
		s->top = pr;
	}
	

	s->num--;

	return 1;	
}

/*
	push:入栈
	s:要入的那个栈
	e：指向要入栈的元素值的空间
		返回值 
			1  入栈成功 
			0  入栈失败
*/
int push(linkstack *s,selemtype *e)
{
	if(s == NULL)
	{
		return 0;
	}

	node *p = malloc(sizeof(*p));  //准备了入栈的数据结点
	p->data = *e;
	p->next = NULL;

	if(s->top == NULL)
	{
		s->top = p;
		s->bottom = p;
	}
	else
	{
		s->top->next = p;
		s->top = p;
	}
	s->num++;

	return 1;
}




