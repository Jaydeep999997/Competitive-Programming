ll powerm(ll a, ll b, ll m = mod)
{
	a %= m;
	ll res = 1 % m;
	while (b > 0)
	{
		if (b & 1)
		{
			res = (res * a) % m;
		}
		b >>= 1;
		a = (a * a) % m;
	}
	return res;
}

void pre()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++)
	{
		fact[i] = (fact[i - 1] * i) % mod;
	}
	ifact[N - 1] = powerm(fact[N - 1], mod - 2);
	for (int i = N - 2; i >= 0; i--)
	{
		ifact[i] = (ifact[i + 1] * (i + 1)) % mod;
	}
}

ll ncr(ll n, ll r)
{
	if (r > n)
	{
		return 0;
	}
	ll ans = (ifact[r] * ifact[n - r]) % mod;
	ans = (ans * fact[n]) % mod;
	return ans;
}

ll incr(ll n, ll r)
{
	if (r > n)
	{
		return 0;
	}
	ll ans = (fact[r] * fact[n - r]) % mod;
	ans = (ans * ifact[n]) % mod;
	return ans;
}

ll npr(ll n, ll r)
{
	if (r > n)
	{
		return 0;
	}
	ll ans = (ifact[n - r] * fact[n]) % mod;
	return ans;
}

ll inpr(ll n, ll r)
{
	if (r > n)
	{
		return 0;
	}
	ll ans = (fact[n - r] * ifact[n]) % mod;
	return ans;
}
