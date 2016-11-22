#define LL long long int
#define MOD 1000000007

//This is the function for Fast Modular Exponential...
//This calculates (base^exp)%MOD...
LL fast_exp(LL base, LL exp) 
{
    LL res = 1;
    while(exp)
    {
       if(exp%2)
            res=(res*base)%MOD;
       base = (base*base)%MOD;
       exp /= 2;
    }
    return res%MOD;
}
