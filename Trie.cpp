struct trie
{
	trie* bt[2];
	int cnt = 0;
};

void Insert(long long x, trie* curr)
{
	for (long long i = bit - 1; i >= 0; i--) // number with atmost "bit" bits
	{
		int b = (x >> i) & 1;
		if (curr->bt[b] == NULL)
		{
			curr->bt[b] = new trie();
		}
		curr = curr->bt[b];
		curr->cnt++;
	}
}


void Remove(long long x, trie* curr)
{
	for (long long i = bit - 1; i >= 0; i--)
	{
		int b = (x >> i) & 1;
		curr = curr->bt[b]; // Assuming that already present
		curr->cnt--;
	}
}

long long maxxor(long long x, trie* curr)
{
	long long ans = 0;
	for (long long i = bit - 1; i >= 0; i--)
	{
		int b = (x >> i) & 1;
		if (curr->bt[!b] != NULL and curr->bt[!b]->cnt > 0)
		{
			ans += (1ll << i);
			curr = curr->bt[!b];
		}
		else
		{
			curr = curr->bt[b];
		}
	}
	return ans;
}
