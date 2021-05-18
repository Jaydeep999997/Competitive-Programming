#define ll long long

const ll B = 11; // Maximum possible base + 1
const ll MX = (1LL << 30) - 1;

ll bit[B]; // maximum bits needed for a given base
ll base;  // Don't forget to initialize base variable globally
vector<ll> pw[B];

struct trie
{
	trie* bt[B];
	int cnt = 0;
};

void prepare()
{
	for (ll b = 2; b < B; b++)
	{
		ll val = 1;
		bit[b] = 0;
		pw[b].push_back(1);
		while (val * b <= MX)
		{
			val *= b;
			bit[b]++;
			pw[b].push_back(val);
		}
	}
}

vector<ll> convert(ll x)
{
	vector<ll> d;
	for (int i = 0; i <= bit[base]; i++)
	{
		d.push_back(x % base);
		x /= base;
	}
	return d;
}

void Insert(ll x, trie* curr)
{
	vector<ll> d = convert(x);
	for (ll i = bit[base]; i >= 0; i--) // number with atmost "bit" bits
	{
		int b = d[i];
		if (curr->bt[b] == NULL)
		{
			curr->bt[b] = new trie();
		}
		curr = curr->bt[b];
		curr->cnt++;
	}
}

void Remove(ll x, trie* curr)
{
	vector<ll> d = convert(x);
	for (ll i = bit[base]; i >= 0; i--)
	{
		int b = d[i];
		curr = curr->bt[b]; // Assuming that already present
		curr->cnt--;
	}

}

ll maxxor(ll x, trie* curr)
{
	ll ans = 0;
	vector<ll> d = convert(x);
	for (ll i = bit[base]; i >= 0; i--)
	{
		ll b = d[i];
		ll go = (base - b) % base;
		ll res = 0;
		for (ll val = 0; val < base; val++)
		{
			ll have = (val + b) % base;
			if (res <= have and curr->bt[val] != NULL and curr->bt[val]->cnt > 0)
			{
				res = have;
				go = val;
			}
		}
		ans += (pw[base][i] * res);
		curr = curr->bt[go];
	}
	return ans;
}

ll minxor(ll x, trie* curr)
{
	ll ans = 0;
	vector<ll> d = convert(x);
	for (ll i = bit[base]; i >= 0; i--)
	{
		ll b = d[i];
		ll go = (base - 1 - b) % base;
		ll res = base - 1;
		for (ll val = 0; val < base; val++)
		{
			ll have = (val + b) % base;
			if (have <= res and curr->bt[val] != NULL and curr->bt[val]->cnt > 0)
			{
				res = have;
				go = val;
			}
		}
		ans += (pw[base][i] * res);
		curr = curr->bt[go];
	}
	return ans;
}



// Problem0: https://judge.yosupo.jp/problem/set_xor_min
// Solution0: https://judge.yosupo.jp/submission/48137, https://pastebin.com/aNELXY0E
