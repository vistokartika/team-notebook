#include<bits/stdc++.h>

using namespace std;

int n,m,u,v,d,num[10005],low[10005],par[10005],child,root,pigeon[10005],nat;
vector<int> adjlist[10005];
vector< pair<int, int> > out;

bool cmp(pair<int, int> x, pair<int, int> y)
{
	if(x.first!=y.first)
	{
		return x.first>y.first;
	}
	return x.second<y.second;
}

void dfs(int now)
{
	num[now]=d;
	low[now]=d;
	d++;
	pigeon[now]=1;
	for(int i=0;i<adjlist[now].size();i++)
	{
		int next=adjlist[now][i];
		if(num[next]==-1)
		{
			par[next]=now;
			dfs(next);
			if(par[now]==-1)
			{
				child++;
			}
			low[now]=min(low[now],low[next]);
			if(low[next]>=num[now])
			{
				pigeon[now]++;
			}
		}
		else if(next!=par[now])
		{
			low[now]=min(low[now],num[next]);
		}
	}
	
	if(par[now]==-1)
	{
		pigeon[now]=child;
	}
}

int main()
{
	while(cin>>n>>m)
	{
		if(n==0 && m==0)
		{
			return 0;
		}
		else
		{
			d=0;
			child=0;
	    	memset(par,-1,sizeof(par));
			memset(num,-1,sizeof(num));
			memset(low,-1,sizeof(low));
			out.clear();
			for(int i=0;i<n;i++)
			{
				adjlist[i].clear();
			}
			while(cin>>u>>v)
			{
				if(u==-1 && v==-1)
				{
					break;
				}
				else
				{
					adjlist[u].push_back(v);
					adjlist[v].push_back(u);
				}
			}
			dfs(0);
			for(int i=0;i<n;i++)
			{
				out.push_back(make_pair(pigeon[i],i));
			}
			sort(out.begin(),out.end(),cmp);
			for(int i=0;i<m;i++)
			{
				cout<<out[i].second<<" "<<out[i].first<<endl;
			}
			cout<<endl;
		}
	}
}
