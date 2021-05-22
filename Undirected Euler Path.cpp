class UndirectedEulerPath
{
 
public:
 
	int n;
	vector<set<int>> adj;
	bool is_path = 1;
	bool is_cycle = 1;
	vector<int> path;
 
	UndirectedEulerPath() {}
 
	UndirectedEulerPath(int _n)
	{
		n = _n;
		adj.resize(n + 1);
		path.clear();
	}
 
	void add_edge(int u, int v)
	{
		adj[u].insert(v);
		adj[v].insert(u);
	}
 
	void dfs(int u)
	{
		while (!adj[u].empty())
		{
			int v = *(adj[u].begin());
			adj[u].erase(adj[u].find(v));
			adj[v].erase(adj[v].find(u));
			dfs(v);
			path.push_back(u);
		}
	}
 
	void solve()
	{
		int cntEdges = 0;
		is_path = is_cycle = 1;
		int src = -1, dest = -1, same = 0;
		for (int i = 1; i <= n; i++)
		{
			cntEdges += adj[i].size();
			if ((int)adj[i].size() % 2 == 0)
			{
				same++;
			}
			else if (src == -1)
			{
				src = i;
			}
			else
			{
				dest = i;
			}
		}
		cntEdges >>= 1;
		is_path &= (same == n || same == n - 2);
		if (!is_path)
		{
			is_cycle = 0;
			return;
		}
		if (src == -1)  // Find first vertex having outgoing edge
		{
			for (int i = 1; i <= n; i++)
			{
				if (!adj[i].empty())
				{
					src = i;
				}
			}
		}
		if (src == -1) // All vertices are isolated (m = 0)
		{
			return;
		}
		path.clear();
		path.push_back(src);
		dfs(src);
		is_path &= ((int)path.size() == cntEdges + 1);
		is_cycle &= (is_path && path[0] == path.back() && dest == -1);
	}
 
};
 

// Problem0: https://cses.fi/problemset/task/1691/
// Solution0: https://cses.fi/paste/721cfe8887ea4c5d217770/,  https://pastebin.ubuntu.com/p/J6Vpqvddyp/
