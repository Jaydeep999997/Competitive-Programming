class DirectedEulerPath
{

public:

	int n;
	vector<vector<int>> adj;
	bool is_path = 1;
	bool is_cycle = 1;
	vector<int> path;

	DirectedEulerPath() {}

	DirectedEulerPath(int _n)
	{
		n = _n;
		adj.resize(n + 1);
		path.clear();
	}

	void add_edge(int u, int v)
	{
		adj[u].push_back(v);
	}

	void dfs(int u)
	{
		while (!adj[u].empty())
		{
			int v = adj[u].back();
			adj[u].pop_back();
			dfs(v);
		}
		path.push_back(u);
	}

	void solve()
	{
		int cntEdges = 0;
		vector<int> inDeg(n + 1, 0);
		vector<int> outDeg(n + 1, 0);
		is_path = is_cycle = 1;
		for (int i = 1; i <= n; i++)
		{
			cntEdges += adj[i].size();
			outDeg[i] += adj[i].size();
			for (auto &j : adj[i])
			{
				inDeg[j]++;
			}
		}
		int src = -1, dest = -1, same = 0;
		for (int i = 1; i <= n && is_path; i++)
		{
			if (abs(inDeg[i] - outDeg[i]) > 1)
			{
				is_path = 0;
			}
			else if (inDeg[i] == outDeg[i])
			{
				same++;
			}
			else if (outDeg[i] == inDeg[i] + 1)
			{
				src = i;
			}
			else if (inDeg[i] == outDeg[i] + 1)
			{
				dest = i;
			}
		}
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
		dfs(src);
		reverse(path.begin(), path.end());
		is_path &= ((int)path.size() == cntEdges + 1);
		is_cycle &= (is_path && path[0] == path.back() && dest == -1);
	}

};


/*


Problem0: https://cses.fi/problemset/task/1693/
Solution0: https://cses.fi/paste/3631491e65a52622217786/, https://pastebin.ubuntu.com/p/K5SXDGsXdR/

Problem1: https://codeforces.com/contest/508/problem/D
Solution1: https://codeforces.com/contest/508/submission/117010081, https://pastebin.ubuntu.com/p/gzxFY6ffMD/

*/
