void bfs(ll id, ll s) // Set inf appropriately
{
	queue<int> mq;
	mq.push(s);
	for (int i = 0; i <= n; i++)
	{
		dis[id][i] = inf;
	}
	dis[id][s] = 0;
	while (!mq.empty())
	{
		auto u = mq.front();
		mq.pop();
		for (auto v : adj[u])
		{
			if (dis[id][v] > 1 + dis[id][u])
			{
				dis[id][v] = 1 + dis[id][u];
				mq.push(v);
			}
		}
	}
}
