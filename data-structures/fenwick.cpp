struct fenwick
{
	int n;
	vector<int> bit;
	fenwick() {}
	fenwick(int n)
	{
		this->n = n + 5;
		bit.resize(n + 5);
	}
	int find(int k)
	{
		int sum = 0, pos = 0;
		for (int i = __lg(n); i >= 0; i--)
		{
			if (pos + (1 << i) < n && sum + bit[pos + (1 << i)] < k)
			{
				sum += bit[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos + 1;
	}
};