bool checkloop(ll u)
{
	if (vis[u] == 1)
	{
		return 1;
	}
	if (vis[u] == 2)
	{
		return 0;
	}
	vis[u] = 1;
	for (auto v : adj[u])
	{
		if (checkloop(v))
		{
			return 1;
		}
	}
	vis[u] = 2;
	return 0;
}
bool cycle()
{
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i] && checkloop(i))
		{
			return true;
		}
	}
	return false;
}
