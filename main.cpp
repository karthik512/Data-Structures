#include<iostream>
#include<list>

using namespace std;

class Graph
{

public:

	int nV;
	bool isDirected;
	list<int> *adjList;
    int *indegree;

Graph(int n,bool dir)
{
    nV = n;
    isDirected = dir;
    adjList = new list<int>[n];
    indegree = new int[nV];
}

Graph(int n)
{
    nV = n;
    isDirected = false;
    adjList = new list<int>[n];
}

void addEdge(int vertex,int nextNode)
{
    adjList[vertex].push_back(nextNode);

    if(!isDirected)
		adjList[nextNode].push_back(vertex);
}

//Prints vertex and it's Adjacency List
void printGraphAdjList()
{
    cout<<"Adjacency Lists of Graph\n";

    for(int i = 0;i < nV;i++)
    {
        list<int>::iterator it;

        cout<<"\nAdjacency of vertex "<<i<<"\n";

        for(it = adjList[i].begin(); it!=adjList[i].end(); ++it)
        {
            cout<<*it;
            cout<<" -> ";
        }
        cout<<"NULL";
        cout<<"\n";
    }
}

//Breadth First Search - Queue Type Implementation
void BFS(int startVertex)
{
    list<int> l;
    bool isVisited[nV];
    for(int i = 0;i < nV;++i)
        isVisited[i] = false;

    l.push_back(startVertex);

    while(!l.empty())
    {
        int t = l.front();
        cout<<t<<" ";
        isVisited[t] = true;
        l.pop_front();

        list<int>::iterator it;
        for(it = adjList[t].begin();it != adjList[t].end();++it)
        {
            if(!isVisited[*it])
            {
                l.push_back(*it);
                isVisited[*it] = true;
            }
        }
    }
}

//Depth First Search Recursive implementation
void DFS(int startVertex)
{
    bool isVisited[nV];

    for(int i=0 ; i<nV ; ++i)
        isVisited[i] = false;

    doDFS(startVertex,isVisited);
}

void doDFS(int v,bool isVisited[])
{
    isVisited[v] = true;

    cout<<v<<" ";

    for(list<int>::iterator it = adjList[v].begin(); it != adjList[v].end() ; ++it)
    {
        if(!isVisited[*it])
        {
            doDFS(*it,isVisited);
        }
    }
}

//Depth First Search Non Recursive implementation - Stack Like Implementation
void DFS2(int startVertex)
{
    bool *isVisited = new bool[nV];
    for(int i = 0; i < nV;i++)
        isVisited[i] = false;

    list<int> l;
    l.push_back(startVertex);
    isVisited[startVertex] = true;

    while(!l.empty())
    {
        int t = l.back();
        cout<<t<<" ";
        l.pop_back();

        list<int>::iterator it;
        for(it = adjList[t].begin();it != adjList[t].end();++it)
        {
            if(!isVisited[*it])
            {
                l.push_back(*it);
                isVisited[*it] = true;
            }
        }
    }
}

bool isCyclic()
{
    if(isDirected)
        return isCyclicDirected();
    else
        return isCyclicUnDirected();
}

bool isCyclicDirected()
{
    bool isVisited[nV];
    bool recStack[nV];

    for(int i = 0;i < nV;++i)
    {
        isVisited[i] = false;
        recStack[i] = false;
    }

    for(int i = 0;i < nV;++i)
    {
        if(isCyclicDirected(i,isVisited,recStack))
            return true;
    }

    return false;
}

bool isCyclicDirected(int v,bool isvisited[],bool recStack[])
{
    if(isvisited[v]==false)
    {
        isvisited[v] = true ;
        recStack[v] =  true ;

        list<int>::iterator it;
        for(it = adjList[v].begin() ; it!= adjList[v].end() ; ++it)
        {
            if(!isvisited[*it]&&isCyclicDirected(*it,isvisited,recStack))
                return true;
            else if(recStack[*it])
                return true;
        }
    }

    recStack[v] = false;

    return false;
}

bool isCyclicUnDirected()
{
    bool isVisited[nV];

    for(int i = 0;i < nV;++i)
        isVisited[i] = false;

    if(isCyclicUnDirected(0,isVisited))
        return true;

    return false;
}

bool isCyclicUnDirected(int v,bool isvisited[])
{
    if(isvisited[v]==false)
    {
        isvisited[v] = true ;

        list<int>::iterator it;
        for(it = adjList[v].begin() ; it!= adjList[v].end() ; ++it)
        {
            if(isvisited[*it])
				return true;
            else
				return isCyclicUnDirected(*it,isvisited);
        }
    }
    return false;
}

void calculateIndegree()
{
    for(int i=0 ; i<nV ;++i)
		indegree[i] = 0;

    for(int i = 0;i<nV;++i)
		for(list<int>::iterator it = adjList[i].begin() ; it != adjList[i].end() ; ++it)
			indegree[*it]++;
}

void printIndegree()
{
    for(int i = 0 ; i<nV ;++i)
        cout<<indegree[i]<<"  ";
}

void topSort()
{
	if(isCyclic())
    {
        cout<<"C";
        return;
    }

	calculateIndegree();

    bool isVisited[nV];

    for(int i = 0;i<nV;++i)
        isVisited[i] = false;

	list<int> stack,topSorted;

	for(int i = 0;i<nV ;++i)
	{
		if(indegree[i] == 0)
		{
            stack.push_back(i);
            isVisited[i] = true;
        }

        while(!stack.empty())
        {
            int v = stack.back();
            stack.pop_back();

            list<int>::iterator it;
            for(it = adjList[v].begin() ; it!= adjList[v].end() ; ++it)
            {
                if(!isVisited[*it])
                {
                    stack.push_back(*it);
                    isVisited[*it] = true;
                }
            }
            topSorted.push_back(v);
        }
    }

	while(!topSorted.empty())
    {
        cout<<topSorted.front()<<"  ";
        topSorted.pop_front();
    }
}

};

int main()
{
   Graph mGraph(5,true);
   mGraph.addEdge(0,1);
   mGraph.addEdge(0,4);
   mGraph.addEdge(1,4);
   mGraph.addEdge(1,2);
   mGraph.addEdge(3,2);
   mGraph.addEdge(4,3);

   cout<<"BFS: ";
   mGraph.BFS(0);
   cout<<"\n";
   cout<<"DFS: ";
   mGraph.DFS2(0);
   cout<<"\n";

   if(mGraph.isCyclic())
        cout<<"\nIt is cyclic\n";
   else
        cout<<"\nNo Cycle\n";

   //mGraph.topSort();

   return 0;
}
