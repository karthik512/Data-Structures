#include <iostream>
#include<list>
#include<queue>
#include<vector>
#include<list>

using namespace std;

int E,V,s;
list<pair<int,int> > adjList[100];
list<pair<int,int> >::iterator it;
priority_queue<pair<int,int>, vector <pair<int,int> >, greater<pair<int,int> > > pq;
int parent[100];
vector<int> dis(100,999);

void findParent(int p)
{
	if(parent[p] == -1)
		return;
		
	findParent(parent[p]);
	printf("%d ",p);
}

void printShDis()
{
	cout<<"Vertes\tSh Dis\tPath\n";
	for(int i = 0;i < V;++i)
	{
		printf("%d\t%d\t%d ",i,dis[i],s);
		findParent(i);
		cout<<"\n";
	}
}

void shortest_path(int source)
{
	dis[source] = 0;
	
	pq.push(make_pair(0,source));
	
	while(!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		for(it = adjList[u].begin();it != adjList[u].end();++it)
		{
			int v = (*it).first;
			int weight = (*it).second;
			
			if(dis[v] > dis[u] + weight)
			{
				parent[v] = u;
				dis[v] = dis[u] + weight;
				pq.push(make_pair(dis[v],v));
			}
		}
	}
}

int main(int argc, char** argv) {
	int u,v,wt;
	
	cin>>V>>E;
	
	for(int i = 0;i < E;++i)
	{
		cin>>u>>v>>wt;
		adjList[u].push_back(make_pair(v,wt));
		adjList[v].push_back(make_pair(u,wt));
	}
	
	for(int i = 0;i < 100;++i)
		parent[i] = -1;
	
	cout<<"Enter source: \n";
	cin>>s;
	
	shortest_path(s);
	printShDis();
	return 0;
}
