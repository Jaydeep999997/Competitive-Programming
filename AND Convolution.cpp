/**
 *  task: https://judge.yosupo.jp/problem/bitwise_and_convolution
 *  reference: https://judge.yosupo.jp/submission/46359
**/

const int MOD = 998244353; // set MOD = -1, if working without mod

template<bool inv, typename T>
void and_convolution(int n, T a[])
{
	if (n == 0)
	{
		return;
	}
	for (int i = 0; i < n / 2; ++i)
	{
		T u = a[i], v = a[i + n / 2]; // butterfly transformation
		if (inv)
		{
			a[i] = -u + v;
			a[i + n / 2] = u;
		}
		else
		{
			a[i] = v;
			a[i + n / 2] = u + v;
		}
	}
	and_convolution<inv>(n / 2, a);
	and_convolution<inv>(n / 2, a + n / 2);
}

template < int mod = -1, typename T >
void and_convolution(int n, T a[], T b[], T res[]) // This will modify a[] and b[], make sure to use temporary array
{
	assert((1 << __lg(n)) == n);
	and_convolution<false>(n, a);
	and_convolution<false>(n, b);
	for (int i = 0; i < n; ++i)
	{
		if (mod != -1)
		{
			a[i] %= mod;
			b[i] %= mod;
		}
		res[i] = a[i] * b[i];
		if (mod != -1)
		{
			res[i] %= mod;
		}
	}
	and_convolution<true>(n, res);
	if (mod != -1)
	{
		for (int i = 0; i < n; ++i)
		{
			res[i] %= mod;
			if (res[i] < 0)
			{
				res[i] += mod;
			}
		}
	}
}

vector<long long> convolve(vector<long long> a, vector<long long> b)
{
	int n = 1;
	while (n < max(a.size(), b.size()))
	{
		n <<= 1;
	}
	a.resize(n);
	b.resize(n);
	vector<long long> ans(n);
	and_convolution<MOD>(n, a.data(), b.data(), ans.data());
	return ans;
}


// Problem0: https://judge.yosupo.jp/problem/bitwise_and_convolution
// Solution0: https://judge.yosupo.jp/submission/48103, https://pastebin.com/BiXBKXpP
