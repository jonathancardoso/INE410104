/*
Author: Jonathan de Oliveira Cardoso (github.com/jonathancardoso)
References:
 - https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
*/
#include <stdio.h>
#define INFINITY 9999
#define MAX 10

//GLOBAL
int kml=0;
float price=0.0;

void dijkstra(int G[MAX][MAX],int n,int startnode, int destination);

void dijkstra(int G[MAX][MAX],int n,int startnode, int destination)
{

	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];

	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	count=1;

	while(count<n-1)
	{
		mindistance=INFINITY;

		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}

			//check if a better path exists through nextnode
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}

	//print the path and distance of each node
	i=destination;
	if(i!=startnode){
		printf("\nDistancia do no %d = %d km",i+1,distance[i]);
		printf("\nRota=%d",i+1);
		j=i;
		do{
			j=pred[j];
			printf("<-%d",j+1);
			}while(j!=startnode);
	}
  printf("\nCusto da viagem: R$%.2f\n",(((float)distance[destination]/kml)*price) );
}

int main(){
	int G[MAX][MAX],i,j,n,u,d;
  printf("Digite o preco do combustivel:\t");
	scanf("%f",&price);
	printf("Digite a autonomia:\t");
	scanf("%d",&kml);
	printf("Digite a quantidade de vertices:\t");
	scanf("%d",&n);
	printf("\nDigite a matriz de adjacencia:\n");

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);

	printf("\nDigite o nó inicial:\t");
	scanf("%d",&u);
  u -= 1;
  printf("\nDigite o destino:\t");
	scanf("%d",&d);
  d -= 1;
	dijkstra(G,n,u,d);

	return 0;
}
