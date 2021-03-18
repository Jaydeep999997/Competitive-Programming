template<typename T>
class Hash   // String indexing starts from 1 , take bigger p
{
public:
	vector<long long> hf, hr, pws, ipws;
	long long p, m, n;

	Hash() {}

	Hash(T &s, long long _p, long long _m)
	{
		n = (int)s.size() - 1;       // Be careful while calculating n
		p = _p;
		m = _m;
		pws.resize(n + 2);
		ipws.resize(n + 2);
		hf.resize(n + 2);
		hr.resize(n + 2);
		pws[0] = 1;
		for (int i = 1; i <= n + 1; i++)
		{
			pws[i] = (pws[i - 1] * p) % m;
		}
		ipws[n + 1] = powerm(pws[n + 1], m - 2, m); // Assuming that m is prime
		for (int i = n; i >= 0; i--)
		{
			ipws[i] = (ipws[i + 1] * p) % m;
		}
		hf[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			ll x = s[i];
			hf[i] = (x * pws[i]) % m;
			hf[i] = (hf[i - 1] + hf[i]) % m;
		}
		hr[n + 1] = 0;
		for (int i = n; i >= 1; i--)
		{
			ll x = s[i];
			hr[i] = (x * pws[n - i + 1]) % m;
			hr[i] = (hr[i + 1] + hr[i]) % m;
		}
	}

	long long getf(int l, int r)
	{
		long long ans = (hf[r] - hf[l - 1] + 2 * m) % m;
		ans = (ans * ipws[l - 1]) % m;
		return ans;
	}

	long long getb(int r, int l)
	{
		long long ans = (hr[l] - hr[r + 1] + 2 * m) % m;
		ans = (ans * ipws[n - r]) % m;
		return ans;
	}
};
