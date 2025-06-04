#include "graph.h"

/*
	create_graph：创建一个图
	返回值 
		返回一个图的指针
*/
mgraph *create_graph()
{	
	int i,j;
	mgraph *g = malloc(sizeof(mgraph));
	g->vexnum = 0;  //顶点数
	g->arcnum = 0;  //边的条数
	printf("please input dingdian\n");
	//先输入图中的每个顶点 
	scanf("%s",g->v);//ABCDE\n
	getchar();  //把后面的\n给消耗掉
	g->vexnum = strlen(g->v);   //测字符串长度即顶点数

	printf("vexnum = %d\n",g->vexnum);
	
	//初始化邻接矩阵，让每个权都为“无穷大”
	for(i = 0; i < g->vexnum; i++)	//二维数组的行 起点下标
	{
		for(j = 0; j < g->vexnum; j++)	//二维数组的列  终点下标
		{
			g->a[i][j] = VERY_BIG;

		}
	}

	//输入每条边的信息  
	//顶点 顶点 w      AB1
	//##0 ->输入结束 
	while(1)
	{	
		char s,p;  //s 表示起点 p 结束点
		int w;  //表示权
		scanf("%c%c%d",&s,&p,&w); 
		getchar();  //把输入的\n给消耗掉 
		if(s == '#')	//遇到'#'表示输入结束
		{
			break;
		}
		//printf("(%c -> %c) = %d\n",s,p,w);

		//获取顶点在顶点数组中的下标 
		int i; //i为起始顶点在顶点数组中的下标
		int j; //j为结束顶点在顶点数组中的下标

		i = get_index(g,s);
		j = get_index(g,p);
		if(i == -1 || j == -1)
		{
			//刚才输入的边信息有误
			printf("input message error\n");
			continue;
		}
		g->a[i][j] = w;


	}
return g;

}
/*
	get_index：获取顶点在顶点数组中的下标
	g:表示从哪个图中的顶点数组中获取就表示哪个图
	s：表示要获取哪个的顶点对应的下标 代表那个顶点
		返回值 
			成功：返回顶点在数组中的下标
			失败：返回-1
*/	

int get_index(mgraph *g,char s)
{	
	int i;
	for(i = 0; i < g->vexnum; i++)
	{
		if(g->v[i] == s)
		{
			return i;
		}	
	}

	return -1;
}
/*
	print_graph:把一个图的邻接矩阵信息打印出来
	g:要打印的那个图
*/
void print_graph(mgraph *g)
{	
	int i,j;
	if(g == NULL)
	{
		return;
	}
	//顶点数组输出 
	for(i = 0; i < g->vexnum;i++)
	{
		printf("%c\t",g->v[i]);
	}
	printf("\n");
	//输出邻接矩阵 
	for(i = 0; i< g->vexnum; i++)  //行 二维数组的前标
	{
		for(j = 0; j < g->vexnum; j++) //列 二维数组的后标
		{
			printf("%d\t",g->a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	

}

//辅助数组 
//用来标记 顶点是否已经被访问过 
//visited[i] = 1 =>g->v[i] 已经被访问过 
//visited[i] = 0 =>g->v[i] 未被被访问过
int visited[MAX];


/*
	DFS：遍历图-》深度优先搜索
	g:需要遍历的图
	v0：从哪个顶点开始出发遍历的下标
*/
void DFS(mgraph *g, int v0)
{
	//访问v0  
	printf("%c ",g->v[v0]);
	//做标记 
	visited[v0] = 1;
	//取v0的第一个邻接点vi
	/*int vi = get_next_adj(g,v0,0);
	//按照同样的规则(深度优先)访问vi及vi的邻接点
	DFS(g,vi);
	//取v0的vi下一个邻接点
	vi = get_next_adj(g,v0,vi) 
	DFS(g,vi);
	...*/
	int u;//为v0的下一个邻接点
	for(u = get_next_adj(g,v0,0);u != -1;u = get_next_adj(g, v0, u+1))
	{
		if(visited[u] == 0)
		{
			DFS(g,u);
		}
				
	}
}




/*
	get_next_adj：取v0的下一个邻接点
	g:要从哪个图中取邻接点 表示那个图
	v0：顶点数组中的顶点的下标
	返回值  
		成功：返回邻接点的下标
		失败：返回-1
*/
int get_next_adj(mgraph *g, int v0, int vi)
{
	int i; 
	for(i = vi; i < g->vexnum; i++)
	{
		if(g->a[v0][i] != VERY_BIG)
		{
			return i;
		}
	}
	return -1;
}
/*
	DFStraver：遍历图-》深度优先搜索(非连通的也可以)
	
*/
void DFStraver(mgraph *g)
{
	int i; 
	//初始化标记数组 
	for(i = 0; i < g->vexnum; i++)
	{
		visited[i] = 0;
	}

	for(i = 0; i < g->vexnum; i++)
	{
		if(visited[i] == 0)
		{
			DFS(g,i);
		}
		
	}
	printf("\n");
}

/*
	BFStraver：广度优先搜索遍历图
	g：需要遍历的图
*/
void BFStraver(mgraph *g)
{	
	//初始化标记数组
	int i; 
	for(i = 0; i < g->vexnum; i++)
	{
		visited[i] = 0;
	}
	//初始化一个队列  
	linkqueue *lk = inintqueue();
	for(i = 0; i < g->vexnum; i++)
	{	
		if(visited[i] == 1)
		{
			continue;
		}
		//访问
		printf("%c ",g->v[i]);
		visited[i] = 1;
		//入队 
		enqueue(lk,i);
		
		while(!queueisempty(lk))
		{
			//出队 
			int v;
			
			dequeue(lk, &v);

			int u;
			for(u = get_next_adj(g,v,0); u!=-1; u =get_next_adj(g,v,u+1))
			{
				if(visited[u] == 0)
				{
					//u未被访问 访问 
					printf("%c ",g->v[u]);
					visited[u] = 1;

					//u入队 
					enqueue(lk,u);
				}

			}
		}
	}

}

int s[MAX];
int dist[MAX];
char path[MAX][MAX]={0}; 
/*
(1)向量(数组) s[n]
	s[i] = 1 :当源点v到vi的最短路径已经求出
		   0 :当源点v到vi的最短路径还没求出

		初始时 	
			s[v] = 1
			其他的s[i] = 0 
		算法的目标就是让所有的s[i] = 1 
	(2)向量(数组) dist[n]
		distance 距离  
			dist[i] 存放的从源点v到vi的(当前的)最短路径的长度 
				初始： 
					dist[i] = w   		若<v,vi>属于R (v到vi有直接路径)
							  无穷大	若<v,vi>不属于R (v 到vi没有直接路径)

	(3)向量(数组) path[][]
		path[i][] 存放的是从源点v到vi的最短路径(v,v1,v2,......,vi)上各经历 
		的顶点。   
			初始时： 
				path[i]={v} 表示从v出发	

	Djkstra：利用Djkstra算法求图g中从v0出发到各顶点  的最短路径
	g：表示图 
	v0：源点
*/
void Djkstra(mgraph *g, int v0)
{	
	int i;
	//初始化三个辅助变量A->ABCDE
	for(i = 0; i < g->vexnum; i++)
	{
		s[i] = 0;
		dist[i] = g->a[v0][i]; //初始值，为v0到vi的直接路径距离
		    			  //path[i]表示从v0到vi的最短路径上经历的顶点
						  //path[i][0]表示最短路径上的源点
						  //path[i][1]v0到vi的最短路径上经历的第二个顶点
						  //...
						  
		path[i][0] = g->v[v0];  //字符数组
		path[i][1] = g->v[i];
	}
	s[v0] = 1;

	int n = 0;
	while(n++ < g->vexnum-1)  //重复上面两个步骤n-1次	
	{
		
		/*step 1:
			从源点v到其他各顶点的第一条路径长度为
				dist[u] = min{dist[w] | w = 0,1,2,3...n-1,且s[w] = 0}; 
			数组 dist[w]的最小值，就是第一条最短路径
				dist[u] 就为当前的最短路径 
				s[u] = 1;
		*/
		int min_dist = VERY_BIG;    //最短路径的长度
		int u;  //dist[]的下标
		for(i = 0; i < g->vexnum; i++)
		{
			if(s[i] == 0)   //从没有找到最短路径中的顶点去找
			{
				if(dist[i] < min_dist)
				{
					min_dist = dist[i];
					u = i;
				}
			}

		}
		//dist[u]就是最短的 
		s[u] = 1;  //找到了最短路径标记为1
		
		/*step 2：  
			对s[w] = 0 (v到w的最短路径还没有求出时)
				更新
				if(dist[u] + <u,w>  < dist[w])
					dist[w] = dist[u] + <u,w>
		
					v到w有一条更近的路径： 
						v ->.....->u -> w
		*/
		for(i = 0; i < g->vexnum; i++)
		{
			if(s[i] == 0)
			{

				if(dist[u] + g->a[u][i] < dist[i])
				{
					dist[i] = dist[u] + g->a[u][i];
					//path[i]也要更新 
					strcpy(path[i],path[u]);
					path[i][strlen(path[i])] = g->v[i];
				}
			}
		}
	}

	//打印出来
	for(i = 0; i < g->vexnum; i++)
	{
		if(i == v0)
		{
			continue;
		}
		//打印的就是源点 终点 距离 最短路径
		printf("%c -> %c [%d] :",g->v[v0],g->v[i],dist[i]);
		int j;
		for(j = 0; j < strlen(path[i]) -1; j++)
		{
			printf("%c ->",path[i][j]);
		}
		printf("%c\n",path[i][j]);

	}
		

}







