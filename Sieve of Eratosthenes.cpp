bool isprime[N];
vector<int> prime;

void sieve()        // Be careful about i*i < N or i<N
{
	for(int i=0;i<N;i++)
	{
		isprime[i]=true;
	}

	isprime[0]=isprime[1]=false;

	for(int i=2;i*i<N;i++)
	{
		if(isprime[i])
		{
			for(int j=i*i;j<N;j+=i)
			{
				isprime[j]=false;
			}
		}
	}

	for(int i=2;i<N;i++)
	{
		if(isprime[i])
		{
			prime.push_back(i);
		}
	}
}
