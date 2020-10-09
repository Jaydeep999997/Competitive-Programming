template<typename T>
class persistent_segtree
{
public:
 
	int n, m;
	vector<int> root, lc, rc;
	vector<T> st;
	int FREE_ID = 0;
 
	persistent_segtree() {}
 
	persistent_segtree(int n_, int m_, T val = T())
	{
		n = n_;
		m = m_;
		FREE_ID = 0;
		root.resize(n + 2);
		st.resize(m + 2, val);
		lc.resize(m + 2);
		rc.resize(m + 2);
	}
 
	T merge(T a, T b)
	{
		T res = a + b;
		return res;
	}
 
	int build(int l, int r) // create one dummy tree
	{
		int node = ++FREE_ID;
		if (l == r)
		{
			return node;
		}
		int mid = (l + r) >> 1;
		lc[node] = build(l, mid);
		rc[node] = build(mid + 1, r);
		return node;
	}
 
	int update(int prev, int ss, int se, int pos, int val)
	{
		int node = ++FREE_ID;
		if (ss == se)
		{
			st[node] = val;
			return node;
		}
		lc[node] = lc[prev];
		rc[node] = rc[prev];
		int mid = (ss + se) >> 1;
		if (pos <= mid)
		{
			lc[node] = update(lc[prev], ss, mid, pos, val);
		}
		else
		{
			rc[node] = update(rc[prev], mid + 1, se, pos, val);
		}
		st[node] = merge(st[lc[node]], st[rc[node]]);
		return node;
	}
 
	T query(int node, int ss, int se, int qs, int qe)
	{
		if (qs > se || qe < ss)
		{
			return T();
		}
		if (qs <= ss && se <= qe)
		{
			return st[node];
		}
		int mid = (ss + se) >> 1;
		T res = merge(query(lc[node], ss, mid, qs, qe), query(rc[node], mid + 1, se, qs, qe));
		return res;
	}
 
};


// Problem: https://codeforces.com/contest/813/problem/E
// Solution: https://pastebin.com/rj9VjQs6
