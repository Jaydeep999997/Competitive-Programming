long long kruskal(int n, vector<pair<long long, pair<int, int>>> &edges) // edges :- {w,{u,v}}
{
	dsu<int> obj(n);  // Add DSU class
	long long cost = 0;
	sort(edges.begin(), edges.end());
	for (int i = 0; i < (int)edges.size(); i++)
	{
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		if (obj.getp(u) == obj.getp(v))
		{
			continue;
		}
		long long w = edges[i].first;
		cost += w;
		obj.merge(u, v);
		tree[u].push_back({v, w});
		tree[v].push_back({u, w});
	}
	return cost;
}
