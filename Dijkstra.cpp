#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define False 0
#define True  1
#define MaxVertexNum 30
#define INF 10000
int v0 = 0;
int D[MaxVertexNum];
int P[MaxVertexNum];
typedef int  VertexType;//顶点 
typedef int  InfoType;	//边 
typedef struct node {
	int adjvertex;	//邻接点域
	InfoType info;	//权值 
	struct node *next; 
}EdgeNode;
typedef struct vnode {
	VertexType vertex;	//顶点
	EdgeNode *firstedge; 
}VertexNode;
typedef struct {
	VertexNode adjust[MaxVertexNum];
	int vertexNUm,edgeNum;
}ALGraph;

//创建图函数 
void CreateALGraph(ALGraph *G)
{
	int i,j,k;
	EdgeNode *p;
	//printf("请输入结点数和边数:(空格隔开)");
	scanf("%d %d",&(G->vertexNUm),&(G->edgeNum));
	//printf("请输入所有顶点信息:(空格隔开)");
	for(i= 0; i < G->vertexNUm; i++)
	{
		scanf("%d",&(G->adjust[i].vertex));
		G->adjust[i].firstedge = NULL;
	}
	//printf("请输入相邻的边的信息与权值:(空格隔开)");
	for(k = 0; k < G->edgeNum; k++)
	{
		scanf("%d %d",&i,&j);
		p =  (EdgeNode *) malloc (sizeof(EdgeNode)); 
		scanf("%d",&(p->info));
		p->adjvertex = j;
		p->next = G->adjust[i].firstedge;
		G->adjust[i].firstedge = p;
	}
}
//Dijkstra算法 
/*
	算法适用于图的邻接表的存储结构
	传入参数：邻接表存储图标一张，起始点，辅助数组
	结果，将辅助数组带回，得到最短路径 (最短路径位于D[]数组中)
*/
void Dijkstra(ALGraph G)
{
	int i,j,w,v;
	int min;
	int final[MaxVertexNum];
	EdgeNode *p;
	memset(D,INF,sizeof(D));	//将全部距离改为INF 
	memset(P,-1,sizeof(P));		//此时全部没有前驱 
	memset(final,False,sizeof(final));
	p = G.adjust[v0].firstedge;	//p为v0指向点的顶点开始指针 
	while(p != NULL)
	{
		D[p->adjvertex] = p->info;	//初始化v0到各个顶点的距离 
		p = p->next;
	}
	D[v0] = 0;
	final[v0] = True;	//初始时v0属于S集合
	/*开始进入主循环，每次求得v0到某个顶点v的最短距离，并加v到S集合*/
	for(i = 1; i < G.vertexNUm; i++)
	{
		v = -1;
		min = INF;
		for(w = 0; w < G.vertexNUm; w++)	//寻找离v0最近的顶点 
		{
			if( (!final[w]) && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		}
		if(v == -1)	break;	//v == -1 表示所有与v0有通路的结点都已经找到了最短路径，则退出循环
		final[v] = True;	//将v加入S集合
		//更新当前最短路径及距离
		p = G.adjust[v].firstedge;
		while(p != NULL)
		{
			if( !(final[p->adjvertex]) && (min + p->info) < D[p->adjvertex])
			{
				D[p->adjvertex] = min + p->info;
				P[p->adjvertex] = v; 
			}
			p = p->next;
		}
	}
}
void Print_ShortestPath(ALGraph G)
{
	int v,i;
	printf("\n%d的最短路径为:(超过100000则认为无路径通过)\n",v0);
	for(v = 0; v < G.vertexNUm; v++)
	{
		//if(P[v] == -1)	continue;
		printf("%-20d",D[v]);
		printf("%d<-",v);
		i = v;
		while(P[i] != -1)
		{
			printf("%d<-",P[i]);
			i = P[i];
		}
		printf("%d\n",v0);
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	/*
		input1.txt:
			6 8
			0 1 2 3 4 5
			0 5 100 0 4 30 0 2 10 1 2 5 2 3 50 3 5 10 4 3 20 4 5 60 
	*/ 
	ALGraph G;
	CreateALGraph(&G);
	Dijkstra(G);
	Print_ShortestPath(G);
	return 0;
}
