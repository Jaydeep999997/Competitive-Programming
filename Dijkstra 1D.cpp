vector<pair<int, long long>> adj[N];
long long dis[N], n;

void dijkstra(int s)
{
	for (int i = 1; i <= n; i++)
	{
		dis[i] = 1e18;
	}
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	dis[s] = 0;
	pq.push({0, s});
	while (!pq.empty())
	{
		auto p = pq.top();
		pq.pop();
		int u = p.second;
		for (auto v : adj[u])
		{
			if (dis[v.first] > dis[u] + v.second)
			{
				dis[v.first] = dis[u] + v.second;
				pq.push({dis[v.first], v.first});
			}
		}
	}
}
