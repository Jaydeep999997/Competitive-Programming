void bfs(ll s)  // Set inf appropriately
{
	queue<int> mq;
	mq.push(s);
	for (int i = 0; i <= n; i++)
	{
		dis[i] = inf;
	}
	dis[s] = 0;
	while (!mq.empty())
	{
		auto u = mq.front();
		mq.pop();
		for (auto v : adj[u])
		{
			if (dis[v] > 1 + dis[u])
			{
				dis[v] = 1 + dis[u];
				mq.push(v);
			}
		}
	}
}
