int n, m;
vector<pair<int, int>> adj[N];
long long dis[N];

void bfs(int s)
{
	for (int i = 1; i <= n; i++)
	{
		dis[i] = 1e9; // set infinity appropriately
	}
	deque<int> q;
	q.push_back(s);
	dis[s] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop_front();
		for (auto &it : adj[u])
		{
			int v = it.first;
			int w = it.second;
			if (dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				if (w == 1)
				{
					q.push_back(v);
				}
				else
				{
					q.push_front(v);
				}
			}
		}
	}
}

// Problem0: https://www.codechef.com/problems/REVERSE
// Solution0: https://pastebin.com/GL8H77QH

// Problem1: https://codeforces.com/contest/1063/problem/B
// Solution1: https://pastebin.com/2AawJwMY
