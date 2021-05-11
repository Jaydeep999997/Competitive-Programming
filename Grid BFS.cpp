int n, m, w = 1;
int a[N][N];
int dis[2][N][N];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool valid(int x, int y)
{
	return (x >= 1 and x <= n and y >= 1 and y <= m and a[x][y] != -1);
}

void bfs(int id, int x, int y)  // int vs long long, w = 1, valid()?
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			dis[id][i][j] = inf;
		}
	}
	dis[id][x][y] = 0;
	queue<pair<int, int>> mq;
	mq.push({x, y});
	while (!mq.empty())
	{
		int u = mq.front().first;
		int v = mq.front().second;
		mq.pop();
		for (int k = 0; k <= 3; k++)
		{
			int nu = u + dx[k];
			int nv = v + dy[k];
			if (valid(nu, nv) and dis[id][nu][nv] > dis[id][u][v] + w)
			{
				dis[id][nu][nv] = dis[id][u][v] + w;
				mq.push({nu, nv});
			}
		}
	}
}

// Problem0: https://codeforces.com/contest/1520/problem/G
// Solution0: https://pastebin.com/m9uGwB8v
