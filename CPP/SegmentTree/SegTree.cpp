#include<iostream>
#include<algorithm>
using namespace std;

#include<string.h>
#include<math.h> 

#define MAX 100002
#define TREE_MAX MAX*3
#define inf 0x7fffffff

int arr[MAX];
int tree[TREE_MAX];

void build_tree(int si, int ss, int se) 
{
    if(ss > se)
        return; // Out of range
  	
  	if(ss == se)
    { 
       // Leaf node
       tree[si] = arr[ss]; // Init value    
       return;
	}
	
    build_tree(si*2+1, ss, (ss+se)/2); // Init left child
	build_tree(si*2+2, 1+(ss+se)/2, se); // Init right child
	
    tree[si] = max(tree[si*2+1], tree[si*2+2]); // Init root value
}

void update_tree(int ss, int ss, int se, int a, int b, int value) 
{
	if(ss > se || ss > b || se < a) // Current segment is not within range [i, j]
		return;
    
  	if(ss == se) 
    {
        // Leaf node
    	tree[node] += value;
        return;
	}

	update_tree(si*2+1, ss, (ss+se)/2, a, b, value); // Updating left child
	update_tree(2+si*2, 1+(ss+se)/2, se, a, b, value); // Updating right child

	tree[si] = max(tree[si*2+1], tree[si*2+2]); // Updating root with max value
}

int query_tree(int si, int ss, int se, int a, int b) {
	
	if(ss > se || ss > b || se < a)
        return -inf; // Out of range

	if(ss >= a && se <= b) // Current segment is totally within range [a, b]
		return tree[si];

	int q1 = query_tree(si*2+1, ss, (ss+se)/2, a, b); // Query left child
	int q2 = query_tree(2+si*2, 1+(ss+se)/2, se, a, b); // Query right child

	int res = max(q1, q2); // Return final result
	
	return res;
}

int main() {
	int N,Q,type,L,R,val;
    
    //No. of elements in array
    cin>>N;
    for(int i = 0; i < N; i++)
        cin>>A[i];
        
	build_tree(0, 0, N-1);
    
    //No. of queries...
    cin>>Q; 
    
    while(Q--)
    {
        cin>>type>>L>>R;
        if(type == 1) // Update
        {
            cin>>val;
            update_tree(0,0,N-1,L,R,val);
        }
        else //Query
            cout<<query_tree(0,0,N-1,L,R);
    }
}
