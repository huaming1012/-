#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
#define maxSize 1000

typedef struct ArcNode //边结点
{
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode //顶点
{
	int id;
	ArcNode *firstarc;
}VNode;
typedef struct AGraph  //图
{
	VNode adjlist[maxSize];
	int numNodes;  //顶点数
}AGraph;

AGraph *read_graph(){
    FILE* fp = fopen("graph_2 adjacency list", "r");
    if(fp == NULL){
        cout << "ERROR" << endl;
    }
    char str[maxSize];
    int num = 0;
    
	AGraph *g;
    g = (AGraph*)malloc(sizeof(AGraph));
    for(int i = 0; i < maxSize; i++){
        g->adjlist[i].firstarc = NULL;
    }
    while(fgets(str, maxSize, fp) != NULL){
        g->adjlist[num].id = num + 1;
        char delims[] = ",";
        char* result  = NULL;
        result = strtok(str, delims);
        while (result != NULL){
            ArcNode *tmp = (ArcNode*)malloc(sizeof(ArcNode));
            tmp->adjvex = atoi(result) - 1;
            tmp->nextarc = g->adjlist[num].firstarc;
            g->adjlist[num].firstarc = tmp;
            result = strtok(NULL, delims);
        }
        num++;
    }
    g->numNodes = num;
    fclose(fp);
    return g;
}

int visited[maxSize]={0};
int count = 0;
int low[maxSize] = {0};


void DFSArticul(AGraph *g, int v0){	//从第v0个顶点出发深度遍历优先遍历图g，查找并输出关节点
	int min = ++count;
	visited[v0]= low[v0] = min;		//v0是第count个访问的顶点
	ArcNode *p;
	for(p = g->adjlist[v0].firstarc; p ; p = p->nextarc)		//对v0的每个邻接顶点检查
	{
		int w = p->adjvex;				//w为v0的邻接顶点
		if(visited[w] == 0)				//w未曾访问，是v0的孩子
		{				
			DFSArticul(g, w);			//返回前求得low[w]

			if(low[w] < min)			//小于，说明还可以在祖先中找到一个回边，记录下该祖先的位置
				min = low[w];
			if(low[w] >= visited[v0])	//low[w]大于等于visited[v0]，说明邻接顶点w的指向的上一级仍然比v0大
				printf("%d ",g->adjlist[v0].id);			//即v0子树上存在一个结点，该结点均没有指向w的祖先的回边
		}
		else if(visited[w] < min)	//w已访问，w是v0在生成树上的祖先
		{
			min = visited[w];
		}
	}
	low[v0] = min;			
}



void FindArticul(AGraph *g){	//连通图G以邻接表作存储结构，查找并输出G上全部关节点。
    printf("cut vertex:\n");
    count = 1;
	int i;
	visited[0] = 1;				//设定邻接表上0号顶点为生成树的根
	for(i = 1; i < g->numNodes; i++)
		visited[i] = 0;
	ArcNode *p = g->adjlist[0].firstarc;
	int v = p->adjvex;
	DFSArticul(g, v);				//从第v顶点出发深度优先查找关节点
	if(count < g->numNodes)			//生成树的根有至少两棵子树
	{
		printf("%d ", g->adjlist[0].id);		//根是关节点，输出
		while(p->nextarc)
		{
			p = p->nextarc;
			v = p->adjvex;
			if(visited[v] == 0)
				DFSArticul(g, v);
		}//while
	}//if
    printf("\n");
}//FindArticul

int time = 0;
int pred[maxSize] = {0};

void DFSvisit(AGraph *g, int v0){ //从第v0个顶点出发深度遍历优先遍历图g，查找并输出bridge边
    low[v0] = visited[v0] = ++time;
    ArcNode *p;
	for(p = g->adjlist[v0].firstarc; p ; p = p->nextarc){ //对v0的每个邻接顶点检查
        int w = p->adjvex;
        if(visited[w] == 0){ //w未曾访问，是v0的孩子
            pred[w] = v0;
            DFSvisit(g, w);
            low[v0] = min(low[v0], low[w]); //更新low[v0]
        }else if(w != pred[v0]){ //w已访问，w是v0在生成树上的祖先
            low[v0] = min(low[v0], visited[w]);  //更新low[v0]
        }
    }
}

void FindBridge(AGraph *g){
    printf("bridge edge:\n");
	time = 0;
	int i;
	for(i = 0; i < g->numNodes; i++) //初始化visited数组
		visited[i] = 0;
    for(i = 0; i < g->numNodes; i++) //初始化low数组
		low[i] = 0; 

    for(i = 0; i < g->numNodes; i++){ //深度优先遍历，计算所有low
        if(visited[i] == 0)
            DFSvisit(g, i);
    }
    for(i = 0; i < g->numNodes; i++){
        int u = pred[i];
        if(u != 0 && visited[i] == low[i])  //输出符合条件的边
            printf("(%d, %d) ", g->adjlist[u].id, g->adjlist[i].id);
    }
    printf("\n");
}

int main(){
    AGraph* G;
    G = read_graph();

    /*for(int i = 0; i < G->numNodes; i++){
        printf("%d: %d:", i, G->adjlist[i].id);
        ArcNode *p;
	    for(p = G->adjlist[i].firstarc; p ; p = p->nextarc){
            printf("%d,", G->adjlist[p->adjvex].id);
        }
        printf("\n");
    }*/
    FindArticul(G);

    FindBridge(G);

    return 0;
}
    