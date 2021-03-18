template<typename T>
class segment	// pass argument as (L,R+1) to process the query from L to R
{
public:
	vector<T> st;
	ll n;
	segment() {}
	segment(ll _n)
	{
		n = _n;
		st.resize(2 * n);
	}
	T merge(T a, T b)
	{
		return max(a, b);
	}
	void create()
	{
		for (ll i = n - 1; i > 0; i--)
		{
			st[i] = merge(st[i << 1], st[(i << 1) | 1]);
		}
	}
	void update(ll idx, T val)
	{
		for (st[idx += n - 1] = val; idx > 1; idx >>= 1)
		{
			st[idx >> 1] = merge(st[min(idx, idx ^ 1)], st[max(idx, idx ^ 1)]);
		}
	}
	T query(ll l, ll r)
	{
		T ans{};
		T ansl{};
		T ansr{};
		for (l += n - 1, r += n - 1; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1)
			{
				ansl = merge(ansl, st[l++]);
			}
			if (r & 1)
			{
				ansr = merge(st[--r], ansr);
			}
		}
		ans = merge(ansl, ansr);
		return ans;
	}
};
