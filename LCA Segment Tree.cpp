class LCA            // Set the ROOT appropriately
{
public:

	int n, root = 1;
	vector<int> tin, euler, depth, st;
	vector<bool> vis;
	vector<vector<int>> adj;

	LCA() {}

	LCA(int _n, int _root = 1)
	{
		root = _root;
		n = _n;
		adj = vector<vector<int>> (n + 1);
		tin = vector<int> (n + 1);
		depth = vector<int> (n + 1);
		vis = vector<bool> (n + 1, 0);
		euler.clear();
		euler.push_back(0);
	}

	void addedge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void reset()
	{
		for (int i = 0; i <= n; i++)
		{
			adj[i].clear();
		}
		adj.clear();
		euler.clear();
	}

	void prepare()
	{
		fill(vis.begin(), vis.end(), false);
		dfs(root, 1);
		int m = (int)euler.size() - 1;
		st.resize(4 * m);
		create(1, 1, m);
	}

	void dfs(int u, int h)
	{
		vis[u] = 1;
		depth[u] = h;
		tin[u] = euler.size();
		euler.push_back(u);
		for (auto to : adj[u])
		{
			if (!vis[to])
			{
				dfs(to, h + 1);
				euler.push_back(u);
			}
		}
	}

	int create(int si, int sl, int sr)
	{
		if (sl == sr)
		{
			return st[si] = euler[sl];
		}
		int mid = (sl + sr) >> 1;
		int lans = create((si << 1), sl, mid);
		int rans = create((si << 1) + 1, mid + 1, sr);
		if (depth[lans] < depth[rans])
		{
			st[si] = lans;
		}
		else
		{
			st[si] = rans;
		}
		return st[si];
	}

	int query(int si, int sl, int sr, int ql, int qr)
	{
		if (sl > qr or sr < ql)
		{
			return -1;
		}
		if (sl >= ql and sr <= qr)
		{
			return st[si];
		}
		int mid = (sl + sr) >> 1;
		int lans = query((si << 1), sl, mid, ql, qr);
		int rans = query((si << 1) + 1, mid + 1, sr, ql, qr);
		if (lans == -1)
		{
			return rans;
		}
		if (rans == -1)
		{
			return lans;
		}
		if (depth[lans] <= depth[rans])
		{
			return lans;
		}
		return rans;
	}

	int lca(int u, int v)
	{
		int l = tin[u];
		int r = tin[v];
		if (l > r)
		{
			swap(l, r);
		}
		return query(1, 1, (int)euler.size() - 1, l, r);
	}
};
