#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkqueue.h"

typedef char vtype;  //图中顶点元素的类型 
typedef int adjtype; //边上权w的类型 

#define MAX 100  //图中顶点的元素的最大个数

#define VERY_BIG 65535 

typedef struct 
{
	vtype v[MAX];  //顶点数组 
	adjtype a[MAX][MAX]; //邻接矩阵的 "边"
	
	int vexnum; //图中有效顶点数
	int arcnum; //图中的边的条数 
	/*
		...
	*/	
}mgraph;

mgraph *create_graph();  			    //创建一个图 
int get_index(mgraph *g,char s);		//获取顶点在数组中的下标 
void print_graph(mgraph *g);			//把一个图的邻接矩阵信息打印出来
void DFS(mgraph *g, int v0);			//遍历图-》深度优先搜索(连通的顶点)

int get_next_adj(mgraph *g, int v0, int vi); //取v0的下一个邻接点

void DFStraver(mgraph *g);				//遍历图-》深度优先搜索(非连通图也可以)

void BFStraver(mgraph *g);				//遍历图-》广度优先搜索(非连通图也可以)

void Djkstra(mgraph *g, int v0);		//求图g中源点v0到其他顶点的最短路径：迪杰斯特拉算法

#endif