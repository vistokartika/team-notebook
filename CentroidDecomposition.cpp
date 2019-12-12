#include <bits/stdc++.h>
using namespace std;
#define int long long int
 
const int mod = 1e9+7;
vector< set<int> > v;//The actual graph
vector<int> par, level, sub;//par[i]==parent of node i in centroid tree, level[i] = level of node i in centroid tree, sub[i] = number of nodes in subarray of i
vector< vector<int> > ans;//ans[i][j]==max wt edge in path from i to j
map< pair<int, int>, int > m;//m[{u, v}] = wieght of edge {u, v}
map<int, pair<int, int> > rank;//index of {u, v} edge
int root;//First centroid of original tree.
void dfsinit(int u, int p)
{
    sub[u] = 1;
    for(int i: v[u])
    {
        if(i==p)continue;
        dfsinit(i, u);
        sub[u]+=sub[i];
    }
}
int findcentroid(int u, int p, int root)
{
    int ret = u;
    for(int i: v[u])
    {
        if(i==p)continue;
        if(sub[i]>=sub[root]/2.)
            ret = findcentroid(i, u, root);
    }
    return ret;
}
void dfs(int u, int p, int lvl, int maxans)
{
 
    ans[lvl][u] = max(ans[lvl][u], maxans);
    for(int i: v[u])
    {
        if(i==p)continue;
        dfs(i, u, lvl, max(maxans, m[{i, u}]));
    }
}
void decompose(int u, int p, int lvl)
{
	dfsinit(u, -1);
	int centroid = findcentroid(u, -1, u);
	if(u==0)root = centroid;
	par[centroid] = p;
	level[centroid] = lvl;
	dfs(centroid, -1, lvl, 0);
	for(int i: v[centroid])
	{
		v[i].erase(centroid);
		decompose(i, centroid, lvl+1);
		v[i].insert(centroid);
	}
}
int query(int a, int b)
{
	int ta = a, tb = b, lcs;
	if(level[ta]>level[tb])
		swap(ta, tb);
	while(level[ta]<level[tb])
		tb = par[tb];
	while(ta!=tb)
		ta = par[ta], tb = par[tb];
	lcs = ta;
	return max(ans[level[lcs]][a], ans[level[lcs]][b]);
}
 
main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int n;
    cin>>n;
    v.resize(n);
    par.resize(n);
    sub.resize(n);
    level.resize(n);
    ans.resize(20, vector<int>(n));
    for(int i = 0;i<n-1;i++)
    {
    	int x, y, c;
    	cin>>x>>y>>c;
    	m[{x-1, y-1}] = m[{y-1, x-1}] = c;
    	v[x-1].insert(y-1);
    	v[y-1].insert(x-1);
    }
    decompose(0, -1, 1);
    //test the centroid tree formed, printing i and parent of i inc entroid tree
    for(int i = 0;i<n;i++)
	cout<<i<<" "<<par[i]<<endl;
    int q = 0;//Take number of queries
    cin>>q;
    while(q--)
    {
    	int a, b;
    	cin>>a>>b;
    	cout<<query(a-1, b-1)<<endl;
    }
 
 
 
    return 0;
} 
