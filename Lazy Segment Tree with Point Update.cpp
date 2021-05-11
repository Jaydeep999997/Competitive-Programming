template<typename T>
class segment
{
public:
	int n;
	vector<T> st;
	vector<bool> isleft;
	vector<long long> lazy;
	vector<long long> a;

	segment() {}

	segment(int _n, vector<long long> &_a)
	{
		n = _n;
		st.resize(4 * n + 10);
		isleft.resize(4 * n + 10, 0);
		lazy.resize(4 * n + 10, 0);
		a = _a;
	}

	T merge(T &a, T &b)
	{
		T res = min(a, b);
		return res;
	}

	void propagate(int si, int l, int r)
	{
		if (l != r)
		{
			isleft[2 * si] = 1;
			isleft[2 * si + 1] = 1;
			lazy[2 * si] += lazy[si];
			lazy[2 * si + 1] += lazy[si];
		}
		st[si] += lazy[si];
		lazy[si] = 0;
		isleft[si] = 0;
	}

	void create(int si, int l, int r)
	{
		if (l == r)
		{
			st[si] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		create(2 * si, l, mid);
		create(2 * si + 1, mid + 1, r);
		st[si] = merge(st[2 * si], st[2 * si + 1]);
	}

	void update(int si, int l, int r, int ql, int qr, int val)
	{
		if (isleft[si])
		{
			propagate(si, l, r);
		}
		if (ql > r or qr<l or l>r)
		{
			return;
		}
		if (ql <= l and qr >= r)
		{
			isleft[si] = 1;
			lazy[si] += val;
			propagate(si, l, r);
			return;
		}
		int mid = (l + r) >> 1;
		update(2 * si, l, mid, ql, qr, val);
		update(2 * si + 1, mid + 1, r, ql, qr, val);
		st[si] = merge(st[2 * si], st[2 * si + 1]);
	}

	void point_update(int si, int l, int r, int id, int val)
	{
		if (l == r)
		{
			st[si] = val;
			return;
		}
		if (l > r)
		{
			return;
		}
		int mid = (l + r) >> 1;
		if (mid >= id)
		{
			point_update(2 * si, l, mid, id, val);
		}
		else
		{
			point_update(2 * si + 1, mid + 1, r, id, val);
		}
		st[si] = merge(st[2 * si], st[2 * si + 1]);
	}

	T query(int si, int l, int r, int ql, int qr)
	{
		if (isleft[si])
		{
			propagate(si, l, r);
		}
		if (ql > r or qr<l or l>r)
		{
			return llinf;
		}
		if (ql <= l and qr >= r)
		{
			return st[si];
		}
		int mid = (l + r) >> 1;
		T ansl = query(2 * si, l, mid, ql, qr);
		T ansr = query(2 * si + 1, mid + 1, r, ql, qr);
		T ans = merge(ansl, ansr);
		return ans;
	}
};

// Problem0: https://codeforces.com/contest/1520/problem/F2
// Solution0: https://pastebin.com/hWkYF2y6
