class LCA   // Set the ROOT appropriately
{
public:

	int n, lg, root;
	vector<int> tin, euler, depth;
	vector<vector<int>> table, adj;
	vector<bool> vis;

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
		for (int i = 0; i < (int)adj.size(); i++)
		{
			adj[i].clear();
		}
		adj.clear();
		for (int i = 0; i < (int)table.size(); i++)
		{
			table[i].clear();
		}
		table.clear();
		euler.clear();
	}

	void prepare()
	{
		fill(vis.begin(), vis.end(), false);
		dfs(root, 1);
		int m = (int)euler.size() - 1;
		lg = log2(m) + 1;
		table = vector<vector<int>> (m + 1);
		for (int i = 0; i <= m; i++)
		{
			table[i] = vector<int> (lg);
		}
		create();
	}

	void dfs(int u, int h)
	{
		vis[u] = 1;
		depth[u] = h;
		tin[u] = (int)euler.size();
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

	void create()
	{
		int m = (int)euler.size() - 1;
		for (int i = 0; i <= m; i++)
		{
			table[i][0] = euler[i];
		}
		for (int j = 1; j < lg; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= m; i++)
			{
				int x = table[i][j - 1];
				int y = table[i + (1 << (j - 1))][j - 1];
				if (depth[x] > depth[y])
				{
					swap(x, y);
				}
				table[i][j] = x;
			}
		}
	}

	int lca(int u, int v)
	{
		if (u == v)
		{
			return u;
		}
		int l = tin[u];
		int r = tin[v];
		if (l > r)
		{
			swap(l, r);
		}
		int x = log2(r - l + 1);
		l = table[l][x];
		r = table[r - (1 << x) + 1][x];
		if (depth[l] > depth[r])
		{
			swap(l, r);
		}
		return l;
	}

};

// Problem: https://codeforces.com/contest/1702/problem/G2
// Solution: https://codeforces.com/contest/1702/submission/167022809
