class LCA       // set the ROOT appropriately
{
public:

	int n, lg, root = 1;
	vector<int> depth;
	vector<vector<int>> parent, adj;

	LCA() {}

	LCA(int _n, int _root = 1)
	{
		root = _root;
		n = _n;
		lg = log2(n) + 1;
		adj = vector<vector<int>> (n + 1);
		parent = vector<vector<int>> (n + 1, vector<int> (lg));
		depth = vector<int> (n + 1);
	}

	void addedge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void reset()
	{
		for (int i = 0; i < (int)adj.size(); i++)
		{
			adj[i].clear();
		}
		adj.clear();
		for (int i = 0; i < (int)parent.size(); i++)
		{
			parent[i].clear();
		}
		parent.clear();
	}

	void prepare()
	{
		for (int i = 0; i < (int)parent.size(); i++)
		{
			for (int j = 0; j < (int)parent[i].size(); j++)
			{
				parent[i][j] = 0;
			}
		}
		dfs(root, 0, 1);
	}

	void dfs(int u, int p, int d)
	{
		depth[u] = d;
		parent[u][0] = p;
		for (int i = 1; i < lg; i++)
		{
			parent[u][i] = parent[parent[u][i - 1]][i - 1];
		}
		for (auto v : adj[u])
		{
			if (v == p)
			{
				continue;
			}
			dfs(v, u, d + 1);
		}
	}

	int lca(int u, int v)
	{
		if (depth[u] < depth[v])
		{
			swap(u, v);
		}
		int diff = depth[u] - depth[v];
		for (int i = lg - 1; i >= 0; i--)
		{
			if ((diff >> i) & 1)
			{
				u = parent[u][i];
			}
		}
		if (u == v)
		{
			return u;
		}
		for (int i = lg - 1; i >= 0; i--)
		{
			if (parent[u][i] && parent[u][i] != parent[v][i])
			{
				u = parent[u][i];
				v = parent[v][i];
			}
		}
		return parent[u][0];
	}

	int ancestor(int u, int k)     // k th ancestor of u
	{
		for (int i = lg - 1; i >= 0; i--)
		{
			if ((k >> i) & 1)
			{
				u = parent[u][i];
			}
		}
		return u;
	}

	int dist(int a, int b)  // set this function appropriately
	{
		return (depth[a] + depth[b] - 2 * depth[lca(a, b)]);
	}

};
