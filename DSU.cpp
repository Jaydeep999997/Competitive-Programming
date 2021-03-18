template<typename T>
class dsu
{
public:
	vector<T> par, sz;
	ll n;
	dsu(ll n_)
	{
		n = n_;
		par.resize(n + 1);
		sz.resize(n + 1);
		for (int i = 0; i <= n; i++)
		{
			par[i] = i;
			sz[i] = 1;
		}
	}
	T getp(T x)
	{
		while (par[x] != x)
		{
			par[x] = par[par[x]];
			x = par[x];
		}
		return x;
	}
	void merge(T a, T b)
	{
		T p1 = getp(a), p2 = getp(b);
		if (p1 == p2)
		{
			return;
		}
		if (sz[p2] > sz[p1])
		{
			swap(p1, p2);
		}
		par[p2] = p1;
		sz[p1] += sz[p2];
		sz[p2] = 0;
	}
};
