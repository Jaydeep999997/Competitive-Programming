// (1) With Modulo

const int mod = 1e9+7;

long long power_mod(long long a,long long b,long long m=mod)
{
    long long res=1;
    a%=m;
    while(b>0)
    {
        if(b&1)
        {
            res=(res*a)%m;
        }
        b>>=1;
        a=(a*a)%m;
    }
    return res;
}


// (2) Without Modulo

template <typename T>

T power(T a,long long b)
{
    T res=1;
    while(b>0)
    {
        if(b&1)
        {
            res=(res*a);
        }
        b>>=1;
        a=(a*a);
    }
    return res;
}
