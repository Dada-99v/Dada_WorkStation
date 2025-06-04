#include <stdio.h>
#include "graph.h"
int main()
{
	mgraph *g = create_graph(); //创建一个图
	//print_graph(g);				//打印图
	//DFStraver(g);				//深度优先搜索遍历图(可以是连通图和非连通图)
	//BFStraver(g);				//广度优先搜索遍历图(可以是连通图和非连通图)
	Djkstra(g, 0);		//求图g中源点v0到其他顶点的最短路径：迪杰斯特拉算法
	return 0;
}