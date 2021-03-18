// indexing start from 0 
// 2k represents k is true (k)
// 2k + 1 represents k is false (!k)
// don't forget to multiply u and v by two while passing

class two_sat
{
public:
 
	int n, tn;
	vector<int> order, comp;
	vector<vector<int>> g, gt;
	vector<bool> way, vis;
 
	two_sat()
	{
 
	}
 
	two_sat(int _n)
	{
		n = _n;
		tn = 2 * n;
		g = vector<vector<int>> (tn);
		gt = vector<vector<int>> (tn);
		vis = vector<bool> (tn, 0);
		way = vector<bool> (n);
		comp = vector<int> (tn, -1);
	}
 
	void dfs1(int u)
	{
		vis[u] = 1;
		for (auto &v : g[u])
		{
			if (!vis[v])
			{
				dfs1(v);
			}
		}
		order.push_back(u);
	}
 
	void dfs2(int u, int id)
	{
		comp[u] = id;
		for (auto &v : gt[u])
		{
			if (comp[v] == -1)
			{
				dfs2(v, id);
			}
		}
	}
 
	void add_edge(int u, int v)  
	{
		g[u].push_back(v);
		gt[v].push_back(u);
	}
 
	void OR(int u, int v)
	{
		add_edge(u ^ 1, v);
		add_edge(v ^ 1, u);
	}
 
	void NAND(int u, int v)
	{
		OR(u ^ 1, v ^ 1);
	}
 
	void implies(int u, int v)
	{
		OR(u ^ 1, v);
	}
 
	void double_implies(int u, int v)
	{
		implies(u, v);
		implies(v, u);
	}
 
	void XOR(int u, int v)
	{
		OR(u, v);
		NAND(u, v);
	}
 
	bool solve_2SAT()
	{
		for (int i = 0; i < tn; i++)
		{
			if (!vis[i])
			{
				dfs1(i);
			}
		}
		reverse(order.begin(), order.end());
		for (int i = 0, j = 0; i < tn; i++)
		{
			int u = order[i];
			if (comp[u] == -1)
			{
				dfs2(u, j++);
			}
		}
		for (int i = 0; i < tn; i += 2)
		{
			if (comp[i] == comp[i + 1])
			{
				return false;
			}
			way[i / 2] = comp[i] > comp[i + 1];
		}
		return true;
	}
};



// Problem1: https://codeforces.com/contest/27/problem/D
// Solution1: https://pastebin.com/R3Xus4SE

// Problem2: https://www.hackerrank.com/contests/proquest/challenges/problem-e-6
// Solution2: https://pastebin.com/dk3yZg89
