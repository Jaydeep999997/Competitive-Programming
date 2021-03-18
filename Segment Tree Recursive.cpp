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
		st.resize(4 * n + 10);
	}
	T merge(T &a, T &b)
	{
		T res;
		res = a + b;
		return res;
	}
	void create(ll l, ll r, ll si)
	{
		if (l == r)
		{
			st[si] = {a[l], a[l]};
			return;
		}
		ll mid = (l + r) >> 1;
		create(l, mid, 2 * si);
		create(mid + 1, r, 2 * si + 1);
		st[si] = merge(st[2 * si], st[2 * si + 1]);
	}
	void updaterange(ll l, ll r, ll si, ll ql, ll qr, ll val)
	{
		if (l == r)
		{
			st[si].ff %= val;
			st[si].ss %= val;
			return;
		}
		ll mid = (l + r) >> 1;
		if (ql <= mid)
		{
			updaterange(l, mid, 2 * si, ql, qr, val);
		}
		if (qr >= mid + 1)
		{
			updaterange(mid + 1, r, 2 * si + 1, ql, qr, val);
		}
		st[si] = merge(st[2 * si], st[2 * si + 1]);
	}
	void updateval(ll l, ll r, ll si, ll idx, ll val)
	{
		if (l == r)
		{
			st[si].ff = val;
			st[si].ss = val;
			return;
		}
		if (idx < l || idx > r)
		{
			return;
		}
		ll mid = (l + r) >> 1;
		if (idx <= mid)
		{
			updateval(l, mid, 2 * si, idx, val);
		}
		else
		{
			updateval(mid + 1, r, 2 * si + 1, idx, val);
		}
		st[si] = merge(st[2 * si], st[2 * si + 1]);
	}
	T query(ll l, ll r, ll si, ll qs, ll qe)
	{
		if (l >= qs && r <= qe)
		{
			return st[si];
		}
		if (l > qe || qs > r)
		{
			return {0, 0};
		}
		ll mid = (l + r) >> 1;
		T ansl = query(l, mid, 2 * si, qs, qe);
		T ansr = query(mid + 1, r, 2 * si + 1, qs, qe);
		T ans = merge(ansl, ansr);
		return ans;
	}
};
