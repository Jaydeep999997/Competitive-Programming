/*

Here we have assumed general case that graph is not necessarily connected

u        -> first vertex in edge
v        -> second vertex in edge
w        -> weight of an edge
adj      -> graph
tree     -> resultant bridge tree of a graph
tin      -> discovery time of a vertex
store    -> id of the bridge component where the vertex belongs to
vertices -> set of vertices which belongs to current bridge component
ap       -> whether vertex is articulation point or not
isBridge -> whether edge is bridge edge or not

Make sure you initialize the variable before using them in appropriate functions

*/


class BCC
{
public:

	int n, m, tim = 0, grp = 0;
	vector<int> u, v, w, tin, minAnc, store;
	vector<vector<pair<int, int>>> adj, tree;
	vector<vector<int>> vertices;
	vector<bool> vis, ap, isBridge;

	BCC() {}

	BCC(int _n, int _m)  // Indexing starts from 1
	{
		n = _n;
		m = _m;
		u = vector<int> (m + 1);
		v = vector<int> (m + 1);
		w = vector<int> (m + 1);
		store = vector<int> (n + 1);
		minAnc = vector<int> (n + 1);
		tin = vector<int> (n + 1);
		vis = vector<bool> (n + 1);
		ap = vector<bool> (n + 1);
		isBridge = vector<bool> (m + 1);
		vertices = vector<vector<int>> (n + 1);
		adj = vector<vector<pair<int, int>>> (n + 1);
		tree = vector<vector<pair<int, int>>> (n + 1);
	}

	// Clears the graph and already available bridge tree
	void reset()
	{
		for (int i = 1; i <= n; i++)
		{
			adj[i].clear();
			tree[i].clear();
			vertices[i].clear();
			vis[i] = 0;
		}
	}

	// Adds an edge with id and weight
	void addedge(int _u, int _v, int _w, int _id)
	{
		int id = _id;
		u[id] = _u;
		v[id] = _v;
		w[id] = _w;
		adj[u[id]].push_back({v[id], id});
		adj[v[id]].push_back({u[id], id});
	}

	// Tells whether edge is bridge or not and vertex is articulation point or not
	void bridgeAndArt()
	{
		fill(vis.begin(), vis.end(), 0);
		fill(ap.begin(), ap.end(), 0);
		fill(isBridge.begin(), isBridge.end(), 0);
		for (int i = 1; i <= n; i++) // Graph may be disconnected
		{
			if (!vis[i])
			{
				tim = 0;
				dfs1(i, -1);
			}
		}
	}

	// This generates bridge tree of the given graph
	void makeTree()
	{
		bridgeAndArt();
		fill(vis.begin(), vis.end(), 0);
		grp = 0;
		for (int i = 1; i <= n; i++) // Graph may be disconnected
		{
			if (!vis[i])
			{
				grp++;
				dfs2(i);
			}
		}
	}

	// Find and mark all bridges and articulation points in given connected component
	void dfs1(int u, int par)
	{
		vis[u] = 1;
		tin[u] = ++tim;
		minAnc[u] = tin[u];
		int deg = 0;
		for (auto v : adj[u])
		{
			int ver = v.first;
			if (ver == par)
			{
				continue;
			}
			deg++;
			if (vis[ver]) // we encountered back edge
			{
				minAnc[u] = min(minAnc[u], tin[ver]);
				continue;
			}
			dfs1(ver, u);
			minAnc[u] = min(minAnc[u], minAnc[ver]);
			if (minAnc[ver] > tin[u])
			{
				isBridge[v.second] = 1;
			}
			if ((par == -1 and deg > 1) or (par != -1 and (minAnc[ver] >= tin[u])))
			{
				ap[u] = 1;
			}
		}
	}

	// Generate bridge tree for the given connected graph
	void dfs2(int u)
	{
		queue<int> Q;
		int comp = grp;
		Q.push(u);
		vis[u] = 1;
		while (!Q.empty()) // current queue explores one bridge component
		{
			int ver = Q.front();
			Q.pop();
			vertices[comp].push_back(ver);
			store[ver] = comp;
			for (auto v : adj[ver])
			{
				int to = v.first;
				int id = v.second;
				if (vis[to])
				{
					continue;
				}
				if (isBridge[id])  // We encountered another bridge component
				{
					grp++;
					tree[comp].push_back({grp, w[id]});
					tree[grp].push_back({comp, w[id]});
					dfs2(to);
				}
				else
				{
					Q.push(to);
					vis[to] = 1;
				}
			}
		}
	}
};
