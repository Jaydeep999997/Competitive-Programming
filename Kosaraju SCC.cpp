vector<ll> adj[N], adjt[N], order;
bool vis[N];
int comp[N];

void dfst(ll u, ll id)
{
	comp[u] = id;
	for (auto v : adjt[u])
	{
		if (comp[v] == -1)
		{
			dfst(v, id);
		}
	}
}

void dfs(ll u)
{
	vis[u] = 1;
	for (auto v : adj[u])
	{
		if (!vis[v])
		{
			dfs(v);
		}
	}
	order.push_back(u);
}

void scc()
{
	for (int i = 0; i <= n; i++)
	{
		comp[i] = -1;
		vis[i] = 0;
	}
	for (int i = 0; i <= n; i++)
	{
		if (!vis[i])
		{
			dfs(i);
		}
	}
	reverse(order.begin(), order.end());
	for (auto i : order)
	{
		if (comp[i] == -1)
		{
			dfst(i, i);
		}
	}
}

void add(ll u, ll v)
{
	adj[u].push_back(v);
	adjt[v].push_back(u);
}
