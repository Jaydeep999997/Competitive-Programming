template<typename T>
class segment
{
public:
	vector<T> st;
	ll n;
	segment() {}
	segment(ll _n)
	{
		n = _n;
		st.resize(4 * n);
	}
	ll get(T &a, ll x)
	{
		ll res = lower_bound(all(a), x) - a.begin();
		return res;
	}
	void create(ll ss, ll se, ll si)
	{
		if (ss == se)
		{
			st[si].push_back(a[ss]);  //Be careful here
			return;
		}
		ll mid = (ss + se) >> 1;
		create(ss, mid, si << 1);
		create(mid + 1, se, si << 1 | 1);
		merge(st[2 * si].begin(), st[2 * si].end(), st[2 * si + 1].begin(), st[2 * si + 1].end(), back_inserter(st[si]));
	}
	ll query(ll ss, ll se, ll si, ll qs, ll qe, ll x)
	{
		if (ss >= qs && se <= qe)
		{
			return get(st[si], x);
		}
		if (ss > qe || qs > se)
		{
			return 0;
		}
		ll mid = (ss + se) >> 1;
		return query(ss, mid, 2 * si, qs, qe, x) + query(mid + 1, se, 2 * si + 1, qs, qe, x);
	}
};
