#include<iostream>
#include<conio.h>

using namespace std;

void LIS(int a[],int n);
void LCS(char c[],char d[],int nc, int nd);
void EditDis(char c[],char d[],int nc,int nd);
void MinCost(int ma[][3],int n,int m);
void coinchange(int s[],int n);
void matmul(int a[],int n);
void Binomial(int n,int k);
void knapsack(int w[],int v[],int cap);
int min(int a, int b, int c);

int main()
{
    //int a[]={10, 22, 9, 33, 21, 50, 41, 60, 80};
    //int a[] = {1,1,2,2};
    //int a[] = {1,2,1,2};
    //int a[] = {1,2,1,2,3};
    //int a[] = {2,3,1,2,1};
    int a[] = {1,3,1,1};
    //int a[] = {2,4,1,3};
 	char c[]="axyt";
 	char d[]="ayzx";
 	int mat[3][3]={{1, 9, 9},
                    {9, 1, 9},
                    {9, 8, 1}};
    int s[] = {1,2,3};
	int mul[] = {2,3,4,5,6};
	int w[] = {1,3,4};
	int v[] = {4,6,7};
	int cap = 5;
 	int sizec = sizeof(c)/sizeof(c[0]);
 	int sized = sizeof(d)/sizeof(d[0]);
 	//cout<<"\nSize: "<<sizec<<" "<<sized<<"\n";
 	int size = sizeof(a)/sizeof(a[0]);


    LIS(a,size);
    //LCS(c,d,sizec-1,sized-1);
    //EditDis(c,d,sizec-1,sized-1);
    //MinCost(mat,2,2);
    //Binomial(4,3);
    //coinchange(s,4);
    //matmul(mul,4);
 	//knapsack(w,v,cap);

 	return 0;
}

//Longest Increasing Subsequence...
//Find the length of longest increasing subsequence where the elements of sub sequence are in increasing order.
void LIS(int a[],int n)
 {
 	int dp[10];
 	int max = 1;

 	for(int i = 0;i < n;i++)
    {
 		dp[i] = 1;
    }

 	for(int i = 1;i < n;i++)
 	{
 		for(int j = 0;j < i;j++)
 		{
 			if(a[i] > a[j] && dp[i] < dp[j] + 1)
 			{
 				dp[i] = dp[j] + 1;
            }
        }
    }

    //Printing the DP Table...
    for(int i = 0;i <= n;i++)
    {
        cout<<dp[i]<<"\t";
    }
/*
    for(int i = 0;i < n;i++)
    {
	 	if(dp[i] > max)
	 	{
		 	max = dp[i];
        }
    }

    cout<<"Length is "<<max<<"\n";
*/
}

//Longest Common Subsequence...
void LCS(char c[],char d[],int nc, int nd)
 {
 	int dp[10][10];

 	for(int i = 0;i <= nc;i++)
    {
 		for(int j = 0;j <= nd;j++)
 		{
 			if(i == 0 || j == 0)
 				dp[i][j] = 0;
            else if(c[i-1] == d[j-1])
 				dp[i][j] = dp[i-1][j-1] + 1;
            else
			 	dp[i][j] = (dp[i-1][j] > dp[i][j-1])?dp[i-1][j]:dp[i][j-1];
        }
    }
 /*
    //Printing the DP Table...
    for(int i = 0;i <= nc;i++)
    {
        for(int j = 0;j <= nd;j++)
        {
            cout<<dp[i][j]<<"\t";
        }
        cout<<"\n";
    }
*/
    //cout<<nc;
    cout<<"Length is "<<dp[nc][nd];
}

//Edit Distance
//No. of operations required to convert String-c to String-d
//The operations allowed are replace, insert and delete
void EditDis(char c[],char d[],int nc,int nd)
{
 	int dp[10][10];
 	int temp;

 	for(int i = 0;i <= nc;i++)
    {
 		for(int j = 0;j <= nd;j++)
 		{
 			if(i == 0)
 				dp[i][j] = j;
            else if(j == 0)
			 	dp[i][j] = i;
            else if(c[i] == d[j])
				dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]) + 1;
        }
    }

 	cout<<dp[nc][nd];
}

void MinCost(int ma[][3],int n,int m)
{
 	int dp[10][10];
 	int temp;

 	for(int i = 0;i <= n;i++)
    {
 		for(int j = 0;j <= m;j++)
 		{
 			if(i == 0 && j == 0)
 				dp[i][j] = ma[0][0];
            else if(i == 0)
			 	dp[i][j] = ma[i][j] + dp[i][j-1];
            else if(j == 0)
			 	dp[i][j] = ma[i][j] + dp[i-1][j];
            else
			 	dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]) + ma[i][j];
        }
    }
    cout<<dp[n][m];
}

void coinchange(int s[],int n)
{
 	int dp[10][10];

 	for(int i=0;i<=3;i++)
    {
 		dp[0][i]=1;
    }

    for(int i=1;i<=n;i++)
    {
	 	dp[i][0]=0;
    }

    for(int i=1;i<=n;i++)
    {
	 	for(int j=1;j<=3;j++)
	 	{
	 		if(j>i)
	 		{
	 			dp[i][j]=dp[i][j-1];
            }
            else
            {
			 	dp[i][j]=dp[i-j][j]+dp[i][j-1];
            }
        }
    }

    for(int i = 0;i <= n;i++)
    {
        for(int j = 0;j <=3;j++)
        {
            cout<<dp[i][j]<<" ";
        }
        cout<<"\n";
    }
    //cout<<dp[n][3];
}

void matmul(int a[],int n)
{
 	int dp[10][10];
 	int q;

 	for(int i=1;i<=n;i++)
    {
 		dp[i][i]=0;
    }

    for(int l=2;l<=n;l++)
    {
        for(int i=1;i<=n-l+1;i++)
        {
	 		int j=i+l-1;
	 		dp[i][j]=1000;

            for(int k=i;k<=j-1;k++)
            {
	 			q=dp[i][k]+dp[k+1][j]+(a[i-1]*a[k]*a[j]);
	 			if(q<dp[i][j])
	 			{
	 				dp[i][j]=q;
                }
            }
        }
    }
    cout<<dp[1][n];
}

//Binomial Coefficient...
void Binomial(int n,int k)
{
 	int dp[10][10];

 	for(int i = 0;i <= n;i++)
    {
 		for(int j = 0;j <= n;j++)
 		{
 			if(j == 0)
 			{
 				dp[i][j] = 1;
            }
            else if(i == j)
            {
			 	dp[i][j] = 1;
            }
            else
            {
			 	dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            }
        }
    }
    cout<<dp[n][k];
}

void knapsack(int w[],int v[],int cap)
{
 	int dp[10][10];

 	for(int i=0;i<=3;i++)
    {
 		for(int j=0;j<=cap;j++)
 		{
 			if(i==0)
 			{
 				dp[i][j]=0;
            }
            else if(w[i-1]<=j)
            {
			 	dp[i][j]=dp[i-1][j]>dp[i-1][j-w[i-1]]+v[i-1]?dp[i-1][j]:dp[i-1][j-w[i-1]]+v[i-1];
            }
            else
            {
			 	dp[i][j]=dp[i-1][j];
            }
        }
    }
    cout<<dp[3][cap];
}

int min(int a, int b, int c)
{
    if(a < b && a < c)
        return a;
    else if(b < a && b < c)
        return b;
    else
        return c;
}
