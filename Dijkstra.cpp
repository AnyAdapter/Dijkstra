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
typedef int  VertexType;//���� 
typedef int  InfoType;	//�� 
typedef struct node {
	int adjvertex;	//�ڽӵ���
	InfoType info;	//Ȩֵ 
	struct node *next; 
}EdgeNode;
typedef struct vnode {
	VertexType vertex;	//����
	EdgeNode *firstedge; 
}VertexNode;
typedef struct {
	VertexNode adjust[MaxVertexNum];
	int vertexNUm,edgeNum;
}ALGraph;

//����ͼ���� 
void CreateALGraph(ALGraph *G)
{
	int i,j,k;
	EdgeNode *p;
	//printf("�����������ͱ���:(�ո����)");
	scanf("%d %d",&(G->vertexNUm),&(G->edgeNum));
	//printf("���������ж�����Ϣ:(�ո����)");
	for(i= 0; i < G->vertexNUm; i++)
	{
		scanf("%d",&(G->adjust[i].vertex));
		G->adjust[i].firstedge = NULL;
	}
	//printf("���������ڵıߵ���Ϣ��Ȩֵ:(�ո����)");
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
//Dijkstra�㷨 
/*
	�㷨������ͼ���ڽӱ�Ĵ洢�ṹ
	����������ڽӱ�洢ͼ��һ�ţ���ʼ�㣬��������
	�����������������أ��õ����·�� (���·��λ��D[]������)
*/
void Dijkstra(ALGraph G)
{
	int i,j,w,v;
	int min;
	int final[MaxVertexNum];
	EdgeNode *p;
	memset(D,INF,sizeof(D));	//��ȫ�������ΪINF 
	memset(P,-1,sizeof(P));		//��ʱȫ��û��ǰ�� 
	memset(final,False,sizeof(final));
	p = G.adjust[v0].firstedge;	//pΪv0ָ���Ķ��㿪ʼָ�� 
	while(p != NULL)
	{
		D[p->adjvertex] = p->info;	//��ʼ��v0����������ľ��� 
		p = p->next;
	}
	D[v0] = 0;
	final[v0] = True;	//��ʼʱv0����S����
	/*��ʼ������ѭ����ÿ�����v0��ĳ������v����̾��룬����v��S����*/
	for(i = 1; i < G.vertexNUm; i++)
	{
		v = -1;
		min = INF;
		for(w = 0; w < G.vertexNUm; w++)	//Ѱ����v0����Ķ��� 
		{
			if( (!final[w]) && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		}
		if(v == -1)	break;	//v == -1 ��ʾ������v0��ͨ·�Ľ�㶼�Ѿ��ҵ������·�������˳�ѭ��
		final[v] = True;	//��v����S����
		//���µ�ǰ���·��������
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
	printf("\n%d�����·��Ϊ:(����100000����Ϊ��·��ͨ��)\n",v0);
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
