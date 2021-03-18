vector<pair<int, long long>> adj[N];
long long dis[M][N], n;

void dijkstra(int id, int s)
{
	for (int i = 1; i <= n; i++)
	{
		dis[id][i] = 1e18;
	}
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	dis[id][s] = 0;
	pq.push({0, s});
	while (!pq.empty())
	{
		auto p = pq.top();
		pq.pop();
		int u = p.second;
		for (auto v : adj[u])
		{
			if (dis[id][v.first] > dis[id][u] + v.second)
			{
				dis[id][v.first] = dis[id][u] + v.second;
				pq.push({dis[id][v.first], v.first});
			}
		}
	}
}
