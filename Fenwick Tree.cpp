template<typename T>
class fenwick
{
public:
	vector<T> fen;
	int n;
 
	fenwick() {}
 
	fenwick(int _n, T val = T())
	{
		n = _n;
		fen = vector<T> (n + 1, val);
	}
 
	T merge(T a, T b)
	{
		return a + b;
	}
 
	void update(int idx, T val)
	{
		while (idx <= n)
		{
			fen[idx] = merge(fen[idx], val);
			idx += (idx & -idx);
		}
	}
 
	T query(int idx)
	{
		T ans{};
		while (idx > 0)
		{
			ans = merge(ans, fen[idx]);
			idx -= (idx & -idx);
		}
		return ans;
	}
 
	T from(int l, int r)
	{
		return query(r) - query(l - 1);
	}
};


// Problem: https://codeforces.com/contest/1430/problem/E
// Solution: https://pastebin.com/1bwhUDau
