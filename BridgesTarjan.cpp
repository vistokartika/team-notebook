#include<bits/stdc++.h>

using namespace std;

int n,m,u,v,d,num[20005],low[20005],par[20005],child,asdf=1;
vector<int> adjlist[20005];
vector< pair< int, int> > out;
bool flag;
char q,p;

void dfs(int now)
{
	num[now]=d;
	low[now]=d;
	d++;
	child=0;
	flag=false;
	for(int i=0;i<adjlist[now].size();i++)
	{
		int next=adjlist[now][i];
		if(num[next]==-1)
		{
			par[next]=now;
			dfs(next);
			child++;
			if(low[next]>num[now])
			{
				int mini=min(now,next);
				int maks=max(now,next);
				out.push_back(make_pair(mini,maks));
			}
			low[now]=min(low[now],low[next]);
		}
		else if(next!=par[now])
		{
			low[now]=min(low[now],num[next]);
		}
	}
}

int main()
{
	while(cin>>n)
	{
		d=0;
		memset(num,-1,sizeof(num));
		memset(low,-1,sizeof(low));
		out.clear();
		for(int i=0;i<n;i++)
		{
			adjlist[i].clear();
		}
		for(int i=0;i<n;i++)
		{
			par[i]=i;
		}
		
		for(int i=0;i<n;i++)
		{
			cin>>u>>q>>m>>p;
			for(int j=0;j<m;j++)
			{
				cin>>v;
				adjlist[u].push_back(v);
				adjlist[v].push_back(u);
			}
		}
		
		for(int i=0;i<n;i++)
		{
			if(num[i]==-1)
			{
				dfs(i);
			}
		}
		sort(out.begin(),out.end());
		if(asdf>1)
		cout<<endl;
		cout<<out.size()<<" critical links"<<endl;
		for(int i=0;i<out.size();i++)
		{
			cout<<out[i].first<<" - "<<out[i].second<<endl;
		}
		asdf++;
	}
	cout<<endl;
}
