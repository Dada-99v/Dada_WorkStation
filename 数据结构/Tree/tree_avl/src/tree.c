#include "tree.h"


/*
	pre_order:先序遍历一棵二叉排序树
	root：表示要遍历的那个树的根
*/
void pre_order(binode *root)
{
	if(root == NULL)
	{
		return;
	}
	printf("%d ",root->data);  //根 
	pre_order(root->lchild);	 //左子树 
	pre_order(root->rchild);	 //右子树
	
}
/*
	mid_order:中序遍历一棵二叉排序树
	root：表示要遍历的那个树的根
*/

void mid_order(binode *root)
{
	if(root == NULL)
	{
		return;
	}
	mid_order(root->lchild);	 //左子树 
	printf("%d ",root->data);  //根 
	mid_order(root->rchild);	 //右子树
	
}
/*
	post_order:后序遍历一棵二叉排序树
	root：表示要遍历的那个树的根
*/
void post_order(binode *root)
{
	if(root == NULL)
	{
		return;
	}
	post_order(root->lchild);	 //左子树 
	post_order(root->rchild);	 //右子树
	printf("%d ",root->data);  //根 
}
/*
	add_a_node:往二叉排序树中添加结点
	t:表示待添加的结点
	返回值  
		成功：返回二叉排序树的根 
		失败：返回NULL
*/

/*
	level_order:按层次遍历 
	root：代表需层次遍历的树根

*/
void level_order(binode *root)
{
	if(root == NULL)
	{
		return; 
	}
	//把根结点入队 
	linkqueue *lk = NULL;
	//初始化一个队列 
	lk = inintqueue();//:分配并初始化一个队列
	enqueue(lk, root);//:入队
							
	while(!queueisempty(lk)) 
		{						
			//队列元素出队
			binode *p = NULL;
			 dequeue(lk, (void **)&p); //p保存了出队元素(结点的指针)
			//访问出队元素
			printf("%d ",p->data);
			//依次把出队元素的左子结点和右子结点入队
			if(p->lchild)
			{
				enqueue(lk, (void *)p->lchild);
			}
			if(p->rchild)
			{
				enqueue(lk, (void *)p->rchild);
			}
			
			
		}								


}




binode * add_a_node(binode *root, telemtype x)
{
	//创建一个结点来保存x  
	binode *p = malloc(sizeof(binode));
	p->data = x;
	p->lchild = p->rchild = NULL;
	p->height = 1;  //一个结点的高度为1
	if(root == NULL)
	{
		return p;
	}



	//1.插入操作 
	root = insert(root,p);
	



	
	//1.找插入位置
	//2.插入
	/*binode *p = root; //查找路径上的最后一个结点
	while(p)
	{
		if(t ->data > p->data)
		{
			if(p ->rchild)  //表示当前比较结点有右孩子
			{
				//往后面去找
				p = p->rchild;
			}
			else  //p ->rchild == NULL
			{
				//此时p就是查找路上的最后一个结点 
				p->rchild = t;
				break;
			}
		}
		else if(t ->data < p ->data)
		{
			if(p ->lchild)
			{
				//往左边去查找 
				p = p ->lchild;
			}
			else
			{
				//此时p是查找路径上的最后一个结点
				p->lchild = t;
				break;
			}
				
		}
		else 
		{
				//相等，不添加。
				//实际可以增加一个结点的引用计数
				return root;
		}
	
	}*/

	return root;	

}
/*
	delete_x:从root指向的二叉排序树中，删除值为x的结点
		并且保证其排序行
	root：指向一棵树的根：从这棵树中删除一个值为x的结点
	返回值： 
		返回删除后的二叉排序树中的根结点
*/
binode *delete_x(binode * root,telemtype x)
{
	if(root == NULL)  //一棵空树 
	{
		return NULL;
	}
	binode *px = NULL;  //指向要删除的结点
	binode *pf = NULL;  //指向要删除的结点px的father结点
	//1.找要删除的结点
	px = root;
	while(px)
	{
		if(px->data == x)		//要删除值等于px指向的当前结点的值
		{
			break;
		}	
		if(x > px->data)		//要删除值大于px指向的当前结点的值
		{
			pf = px;
			px = px ->rchild;
		}
		else					//要删除值小于px指向的当前结点的值
		{
			pf = px;
			px = px->lchild;
		}

	}

	if(px == NULL)		//该二叉排序树中没有结点的值等于x
	{
		return root;
	}
	//否者 px指向要删除的结点
delete:	
	//2.分情况删除
	if(px->lchild == NULL && px->rchild == NULL) //要删除的结点的左孩子和右孩子都为空
	{
		//要删除的结点px可能为根结点
		//也有可能为叶子结点，整棵树中只有一个结点
		if(px == root)
		{
			free(px);
			return NULL;
		}
		//px为叶子结点，pf为px的父结点 你要判断px是pf的哪个孩子结点 左 右
		if(px == pf ->lchild)
		{
			pf->lchild = NULL;		
		}
		else
		{
			pf->rchild = NULL;		
		}	
		free(px);
		return root;
	}
	else if(px ->lchild == NULL)			//要删除的结点的左孩子为空右孩子不为空
	{
		if(px == root)
		{
			root = px ->rchild;
			px->rchild = NULL;
			free(px);
			return root;
		}
		if(pf->lchild == px)
		{
			pf->lchild = px ->rchild;
			px ->rchild = NULL;
			free(px);
			return root;
		}
		else
		{
			pf->rchild = px ->rchild;
			px->rchild = NULL;
			free(px);
			return root;
		}	
		
	}
	else if(px ->rchild == NULL)			//要删除的结点的右孩子为空左孩子不为空
	{
		if(px == root)
		{
			root = px ->lchild;
			px->lchild = NULL;
			free(px);
			return root;
		}
		if(pf->lchild == px)
		{
			pf->lchild = px ->lchild;
			px->lchild = NULL;
			free(px);
			return root;
		}
		else 
		{
			pf->rchild = px->lchild;
			px->lchild = NULL;
			free(px);
			return root;
		}
		
	}
	else									//要删除的结点左右孩子都不为空
	{
		//正真要删除的结点还没有找到"替罪羊"
		binode *px1 = px ->lchild;   //px1指向px的左子树中的最大结点
										//px1是真正要删除的结点
		pf = px;		//指向px1的父结点  

		while(px1->rchild)
		{
			pf = px1;
			px1 = px1->rchild;		
		}
		//把px1的数据域拷贝给px
		px->data = px1->data;

		px = px1;  //px还是指向要删除的结点
		
		goto delete;
	
	}
	
}
/*
	insert：往平衡二叉树中增加一个结点
			后仍然保存平衡 
	root：表示需要增加结点的平衡二叉排序树
	t：需要增加的那个结点 

*/
binode *insert(binode *root,binode *p)
{
	if(root == NULL)
	{
		return p;
	}
	if(p->data > root->data)	//插入的结点的数据比根结点的大
	{
		root->rchild = insert(root->rchild,p);
		root ->height = max(h(root->lchild), h(root->rchild)) + 1;
		//插入p后，可能会导致root不平衡
		//如果root不平衡啦，则需要对root进行一个平衡处理
		if(h(root->rchild) - h( root->lchild)  > 1)
		{
			//不平衡了  
			if(p ->data > root ->rchild->data)
			{
				//p是添加在 root的右子结点的右边，导致root不平衡 
				//此时，应该进行一个“单向左旋平衡处理”
				return singlerotatewithleft(root);
				
			}
			else if(p->data < root->rchild->data)
			{
				//p是添加在root的右子结点的左边，导致root不平衡
				//此时，应该进行一个双向旋转(先右后左)

				return doublerotaterightleft(root);
				
			}
			
		}

		
	}
	else if(p->data < root->data)	//插入的结点的数据比根结点的小
	{	
		root->lchild = insert(root->lchild,p);
		root->height = max(h(root ->lchild),h(root->rchild))+ 1;
		//插入p后，可能会导致root不平衡
		//如果root不平衡，则需要对root进行一个平衡处理 
		if(h(root ->lchild) - h(root->rchild) > 1)
		{
			if(p->data < root->lchild->data)
			{
				//p是添加在 root的左子结点的左边，导致root不平衡的
				//此时，应该进行一个“单向右旋平衡处理”
				return singlerotatewithright(root);
			}
			else if(p ->data > root->lchild->data)
			{
				//p是添加在,root的左子结点的右边，导致root不平衡的
				//此时，应该进行一个双向旋转(先左后右)
				return doublerotateleftright(root);
			}
		
		}
	}
	else				//插入的结点的数据跟根结点的相等
	{
			//不做处理
	}
	return root;
}


/*
	h:求一棵树的高度
	t:表示要求高度的树的根
	返回值： 
		返回树的高度
*/
int h(struct binode *t)
{
	if(t == NULL)
	{
		return 0;
	}
	/*else 
	{
		int l = h(t->lchild);
		int r = h(t->rchild);
		return l>r ? l + 1 : r + 1;
	}*/
	return t->height;					
}

/*
	singlerotatewithleft：对k进行单向左旋平衡处理
	k：要进行单向左旋平衡处理的树根
	返回值  
		返回旋转后的新的根结点
*/
binode *singlerotatewithleft(binode *k)
{	
	binode *k1 = k->rchild;
 	k->rchild = k1->lchild;  
 	k1->lchild = k; 
	//重新计算k，k1的高度 
	k->height = max(h(k->lchild),h(k->rchild)) + 1;
	k1->height = max(h(k1->lchild),h(k1->rchild)) + 1;
	//k1 作为平衡后的根结点 
	return k1;
}

/*
	singlerotatewithright:对k进行单向右旋平衡处理
	k：要进行单向右旋平衡处理的树根
	返回值  
		返回旋转后的新的根结点
*/
binode *singlerotatewithright(binode *k)
{
	binode *k1 = k ->lchild;
	k->lchild = k1->rchild;
	k1->rchild = k;
	//重新计算k k1的高度 
	k->height = max(h(k->lchild),h(k->rchild)) + 1;
	k1->height = max(h(k1->lchild),h(k1->rchild)) + 1;
	//k1作为这棵树的根结点
	return k1;
}
/*
	doublerotateleftright：对k进行一个先左后右的双向旋转
	k：要进行先左后右旋转的结点
	返回值  
		返回旋转后的新的根结点
*/
binode *doublerotateleftright(binode *k)
{
	k->lchild = singlerotatewithleft(k->lchild);
	return singlerotatewithright(k);

}
/*
	doublerotaterightleft：对k进行一个先右后左的双向旋转
	k：要进行先右后左旋转的结点
	返回值  
		返回旋转后的新的根结点
*/

binode *doublerotaterightleft(binode *k)
{
	k->rchild = singlerotatewithright(k->rchild);
	return singlerotatewithleft(k);
}






