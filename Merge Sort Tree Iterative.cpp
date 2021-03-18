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
	ll get(T &a, ll x)
	{
		ll res = lower_bound(all(a), x) - a.begin();
		return res;
	}
	void create()
	{
		for (ll i = n - 1; i > 0; i--) // merging vectors
		{
			merge(st[i << 1].begin(), st[i << 1].end(), st[(i << 1) | 1].begin(), st[(i << 1) | 1].end(), back_inserter(st[i]));
		}
	}
	ll query(ll l, ll r, ll x)
	{
		ll ans{};
		ll ansl{};
		ll ansr{};
		for (l += n - 1, r += n - 1; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1)
			{
				ll id = get(st[l], x); // set the function accordingly
				l++;
				ansl += id;
			}
			if (r & 1)
			{
				--r;
				ll id = get(st[r], x);
				ansr += id;
			}
		}
		ans = ansl + ansr;
		return ans;
	}
};
