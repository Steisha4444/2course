
#include<stdio.h>
#include<conio.h>
#include <iostream>
#include <fstream>

#define INFINITY 9999
#define MAX 10
using namespace std;
class graph {
public:
	int distance[MAX];
	int pred[MAX];
	int roud[MAX];
};
void dijkstra(int G[MAX][MAX], int n, int startnode);

int main()
{
	ifstream f_in;
	f_in.open("map.txt");
	
	int G[MAX][MAX], i, j, n, u;
	printf("Enter no. of vertices:");
//	int G[MAX][MAX];
	f_in >> n;
	printf("\nEnter the adjacency matrix:\n");

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		
			f_in >> G[i][j];

	printf("\nEnter the starting node:");
	
	f_in >> u;
	dijkstra(G, n, u);

	return 0;
}

void dijkstra(int G[MAX][MAX], int n, int startnode)
{
	graph g1;
	int cost[MAX][MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;
	//int roud[MAX];
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];

	for (i = 0; i < n; i++)
	{
		g1.distance[i] = cost[startnode][i];
		g1.pred[i] = startnode;
		visited[i] = 0;
		g1.roud[i] = 1;
	}

	g1.distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	while (count < n - 1)
	{
		mindistance = INFINITY;

		//nextnode дає вершину на мінімальній відстані
		for (i = 0; i < n; i++)
			if (g1.distance[i] < mindistance && !visited[i])
			{
				mindistance = g1.distance[i];
				nextnode = i;
			}

		//перевірити, чи існує кращий шлях через nextnode			
		visited[nextnode] = 1;
		for (i = 0; i < n; i++){
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < g1.distance[i])
				{
					g1.distance[i] = mindistance + cost[nextnode][i];
					g1.pred[i] = nextnode;
					
				
					
				}
		}
		count++;
	}

	
	for (i = 4; i < n; i++)
		if (i != startnode)
		{
			

			j = i;
			printf("%d", i);
			do
				
			{
				
				j = g1.pred[j];
				printf("<-%d", j);
				g1.roud[i]++;
			} while (j != startnode);
		}
	int temp = 0;
	int index[MAX];
	int tmp =900 ;
	for (i = 0; i < n; i++) {
		if (g1.roud[i] >= temp) {
			temp = g1.roud[i];
		}
	
	}

	for (i = 0; i < n; i++) {
		if (g1.roud[i] == temp) {
			index[i] = i;
		}
		else
			index[i] = 0;
	}

	for (i = 0; i < n; i++) {
		if (index[i] != 0)
		{
			if (g1.distance[i] < tmp)
			{
				tmp = g1.distance[i];
				temp = i;

			}
		}
	}
	cout << "\nDintances " << tmp << "country no " << temp << endl;
	//cout << "Dintance min " << distance[i] << "country" << temp << endl;
}

