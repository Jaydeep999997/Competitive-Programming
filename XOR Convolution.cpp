/**
 *  task: https://judge.yosupo.jp/problem/bitwise_xor_convolution
 *  reference: https://judge.yosupo.jp/submission/46360
**/


const int MOD = 998244353; // set MOD = -1, if working without mod

template<bool inv, typename T>
void xor_convolution(int n, T a[]) // performs DFT
{
	if (n == 0)
	{
		return;
	}
	for (int i = 0; i < n / 2; ++i)
	{
		T u = a[i], v = a[i + n / 2]; // butterfly transformation
		a[i] = u + v;
		a[i + n / 2] = u - v;
		if (inv)
		{
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}
	}
	xor_convolution<inv>(n / 2, a);
	xor_convolution<inv>(n / 2, a + n / 2);
}

template < int mod = -1, typename T >
void xor_convolution(int n, T a[], T b[], T res[]) // This will modify a[] and b[], make sure to use temporary array
{
	assert((1 << __lg(n)) == n);
	xor_convolution<false>(n, a);
	xor_convolution<false>(n, b);
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
	xor_convolution < mod == -1 > (n, res);
	if (mod != -1)
	{
		assert(mod % 2);     // mod must be odd here
		const int r2 = (mod + 1) / 2;
		int rn = 1;
		for (int i = 0; i < __lg(n); ++i)
		{
			rn = 1LL * rn * r2 % mod;
		}
		for (int i = 0; i < n; ++i)
		{
			res[i] %= mod;
			if (res[i] < 0)
			{
				res[i] += mod;
			}
			res[i] = 1LL * res[i] * rn % mod;
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
	xor_convolution<MOD>(n, a.data(), b.data(), ans.data());
	return ans;
}

Problem0: https://judge.yosupo.jp/problem/bitwise_xor_convolution
Solution0: https://judge.yosupo.jp/submission/48100, https://pastebin.com/ADhC3T5k
