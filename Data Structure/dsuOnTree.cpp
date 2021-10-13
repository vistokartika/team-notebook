int n;
vector<int> edge[100005];
vector<int> *vec[100005];
int col[100005];
int sz[100005];
int cnt[100005];
int ans[100005];

void dfs(int u, int p = -1, bool keep = true)
{
	pii mx = {-1, -1};
	for(int v : edge[u])
	{
		if(v == p) continue;
		mx = max(mx, {sz[v], v});
	}

	for(int v : edge[u])
	{
		if(v == p) continue;
		if(v == mx.se) continue;
		dfs(v, u, false);
	}

	if(mx.se != -1)
		dfs(mx.se, u), vec[u] = vec[mx.se];
	else
		vec[u] = new vector<int>();

	vec[u]->pb(u);
	++cnt[col[u]];

	for(int v : edge[u])
	{
		if(v == p) continue;
		if(v == mx.se) continue;
		for(int x : *vec[v])
		{
			vec[u]->pb(x);
			++cnt[col[x]];
		}
	}

	if(keep == 0)
		for(int v : *vec[u])
			--cnt[col[v]];

	
}

void sSZ(int u, int p = -1)
{
	sz[u] = 1;
	for(int v : edge[u])
	{
		if(v == p) continue;
		sSZ(v, u);
		sz[u] += sz[v];
	}
}