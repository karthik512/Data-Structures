#include <iostream>

using namespace std;

int A[100];
int BIT[100];

void buildBIT(int n)
{
    int k,v;

    for(int i = 1;i <= n;++i)
    {
        v = A[i-1];
        k = i;

        while(k <= n)
        {
            BIT[k] += v;
            k += k&(-k);
        }
    }
}

void updateBIT(int index,int value,int n)
{
    int in = index+1;

    while(in <= n)
    {
        BIT[in] += value;
        in += in&(-in);
    }
}

int queryBIT(int R, int n)
{
    if(R < 0) return 0;

    int ans = 0;
    int in = R+1;

    while(in > 0)
    {
        ans += BIT[in];
        in -= in&(-in);
    }

    return ans;
}

int main()
{
    int N,Q,type,x,y,v;

    cout<<"Enter N: \n";
    cin>>N;

    for(int i = 0;i < N;++i)
        cin>>A[i];

    buildBIT(N);

    cin>>Q;

    while(Q--)
    {
        cin>>type;
        if(type == 0) //Update Operation
        {
            cin>>x>>y>>v;
            for(int i = x;i <= y;++i)
                updateBIT(i,v,N);
        }
        else if(type == 1)  //Query Sum Operation
        {
            cin>>x>>y;
            int a = queryBIT(y,N);
            int b = queryBIT(x-1,N);
            cout<<"Ans: "<<(a-b)<<"\n";
        }
    }

    return 0;
}
