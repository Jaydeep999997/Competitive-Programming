vector<pair<int, long long>> adj[N];
int n, par[N];
bool vis[N];
vector<pair<int, long long>> tree[N];

void prim(int s)  // edges u -> {v,weight}
{
	for (int i = 1; i <= n; i++)
	{
		par[i] = 0;
		vis[i] = 0;
	}
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	pq.push({0, s});
	long long cost = 0;
	par[s] = 0;
	while (!pq.empty())
	{
		int u = pq.top().second;
		long long w = pq.top().first;
		pq.pop();
		if (vis[u]) // We are creating tree as a by expanding single connected component only
		{
			continue;
		}
		cost += w;
		vis[u] = 1;
		if (u != s) // Be careful here
		{
			tree[u].push_back({par[u], w}); // It will add unnecessary edge between source and 0
			tree[par[u]].push_back({u, w});
		}
		for (auto v : adj[u])
		{
			if (vis[v.first])
			{
				continue;
			}
			par[v.first] = u;
			pq.push({v.second, v.first});
		}
	}
}
