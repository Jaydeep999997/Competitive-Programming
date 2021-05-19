// reference: https://cp-algorithms.com/graph/edmonds_karp.html


#define int long long   // Overflow !
#define INF 9223372036854775807

int n, m;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;
	queue<pair<int, int>> q;
	q.push({s, INF});

	while (!q.empty()) {
		int cur = q.front().first;
		int flow = q.front().second;
		q.pop();

		for (int next : adj[cur]) {
			if (parent[next] == -1 && capacity[cur][next]) {
				parent[next] = cur;
				int new_flow = min(flow, capacity[cur][next]);
				if (next == t)
					return new_flow;
				q.push({next, new_flow});
			}
		}
	}

	return 0;
}

int maxflow(int s, int t) {
	int flow = 0;
	vector<int> parent(n);
	int new_flow;

	while ((new_flow = bfs(s, t, parent))) {
		flow += new_flow;
		int cur = t;
		while (cur != s) {
			int prev = parent[cur];
			capacity[prev][cur] -= new_flow;
			capacity[cur][prev] += new_flow;
			cur = prev;
		}
	}

	return flow;
}



Problem0: https://cses.fi/problemset/task/1694/
Solution0: https://cses.fi/paste/e15473b18e0b78a92133ef/, https://pastebin.com/kNKNvFRQ
