const int K = 2;

int n, m;
vector<pair<int, int>> adj[N];
long long dis[N];
vector<int> q[K];
bool vis[N];

// s: source vertex
// k: values of the edges can be from 0 to k, so we need to take modulo by (k+1)

void bfs(int s, int k)
{
	for (int i = 1; i <= n; i++)
	{
		dis[i] = 1e9; // set infinity appropriately
		vis[i] = false;
	}
	for (int i = 0; i <= k; i++) // clear this for multiple testcases
	{
		q[i].clear();
	}
	dis[s] = 0;
	q[0].push_back(s);
	int inside = 1; // number of vertices inside the queue right now
	int pos = 0;
	while (inside > 0)
	{
		while (q[pos].empty())
		{
			pos = (pos + 1) % (k + 1);
		}
		int u = q[pos].back();
		q[pos].pop_back();
		--inside;
		if (vis[u])
		{
			continue;
		}
		vis[u] = true;
		for (auto &it : adj[u])
		{
			int v = it.first;
			int w = it.second;
			if (dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				q[dis[v] % (k + 1)].push_back(v);
				++inside;
			}
		}
	}
}


// Tutorial: https://codeforces.com/blog/entry/88408

// Problem0: https://www.codechef.com/problems/REVERSE
// Solution0: https://pastebin.com/DTfvTviu
