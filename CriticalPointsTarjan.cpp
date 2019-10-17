#include<bits/stdc++.h>

using namespace std;

int n,m,u,v,d,num[105],low[105],par[105],child,arr[105],root,cnt;
vector<int> adjlist[105];
bool flag;

void dfs(int now)
{
	num[now]=d;
	low[now]=d;
	d++;
	for(int i=0;i<adjlist[now].size();i++)
	{
		int next=adjlist[now][i];
		if(num[next]==-1)
		{
			par[next]=now;
			dfs(next);
			if(root==now)
			{
				child++;
			}
			if(low[next]>=num[now])
			{
				arr[now]=1;
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
	ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    while(cin>>n)
    {
    	d=1;
    	cnt=0;
    	memset(arr,0,sizeof(arr));
    	memset(par,-1,sizeof(par));
		memset(num,-1,sizeof(num));
		memset(low,-1,sizeof(low));
		for(int i=1;i<=n;i++)
		{
			adjlist[i].clear();
		}
		
    	if(n==0)
    	{
    		return 0;
		}
    	string s;
        while (getline(cin, s))
        {
        	if(s=="0")
        	{
				break;
			}
            stringstream ss(s);
            int u, v;
            ss >> u;
            while (ss >> v)
            {
                adjlist[u].push_back(v);
                adjlist[v].push_back(u);
            }
        }
		for(int i=1;i<=n;i++)
		{
			if(num[i]==-1)
			{
				root=i;
				child=0;
				dfs(i);
				if(child>1)
				{
					arr[i]=1;
				}
				else
				{
					arr[i]=0;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(arr[i]>0)
			{
				cnt++;
			}
		}
		cout<<cnt<<endl;
    }
}

//Finding articulation points and bridges in a general graph

const int GraphSize = 1000;
int root, child, counter;
int num[GraphSize], low[GraphSize], parent[GraphSize];
bool artpoint[GraphSize];
vector<int> adjlist[GraphSize];

void tarjan(int front){
	low[front] = num[front] = counter++;
	int sz = adjlist[front].size();
	for(int i = 0; i < sz; i++){
		if(num[adjlist[front][i]] == -1){
			parent[adjlist[front][i]] = front;
			if(parent[front] == root){
				child++;
			}

			tarjan(adjlist[front][i]);

			if(low[adjlist[front][i]] >= num[front]){
				artpoint[front] = true;
			}
			if(low[adjlist[front][i]] > num[front]){
				//prints bridge
				cout << "Edge from " << front << " to " << adjlist[front][i] << " is a bridge\n";
			}
			low[front] = min(low[front], low[adjlist[front][i]]);
		}
		else if(adjlist[front][i] != parent[front]){
			low[front] = min(low[front], num[adjlist[front][i]]);
		}
	}
}

void solve(int v){
	//v is the number of vertices
	counter = 0;
	memset(num, -1, sizeof(num));
	memset(low, 0, sizeof(low));
	for(int i = 0; i < v; i++){
		if(num[i] == -1){
			root = i;
			child = 0;
			tarjan(i);
			if(child > 1)
				artpoint[i] = true;
		}
	}
}
