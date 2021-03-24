long long d[N][N], fun[N][N];
long long u[M], v[M], w[M];
vector<pair<int, long long>> adj[N];
int n, m;
 
void floyd_warshall()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			d[i][j] = 1e15;  // set infinity appropriately
		}
		d[i][i] = 0;
	}
	for (int i = 1; i <= m; i++)
	{
		d[u[i]][v[i]] = min(d[u[i]][v[i]], w[i]);
		d[v[i]][u[i]] = min(d[v[i]][u[i]], w[i]);
	}
	for (int mid = 1; mid <= n; mid++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				d[i][j] = min(d[i][j], d[i][mid] + d[mid][j]);
			}
		}
	}
}

// Problem0: https://codeforces.com/contest/1483/problem/D
// Solution0: https://pastebin.com/jsCmMM38
