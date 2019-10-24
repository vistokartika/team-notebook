const int GraphSize = 1000;
int root, child, counter, n, m, u, v;
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

void solve(int n){
	//n is the number of vertices
	counter = 0;
	memset(num, -1, sizeof(num));
	memset(low, 0, sizeof(low));
	for(int i = 0; i < n; i++){
		if(num[i] == -1){
			root = i;
			child = 0;
			tarjan(i);
			if(child > 1)
				artpoint[i] = true;
		}
	}
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		cin >> u >> v;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
	}
	solve(n);
	for(int i = 0; i < n; i++) {
		if(artpoint[i] == true) {
			cout << i << " is articulation point" << endl;
		}
	}
}

// SCC
int n,m,u,v,d,num[10005],low[10005],par[10005],child,root,pigeon[10005],nat;
vector<int> adjlist[10005];

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

// pigeon[i] is scc of node i

int main() {
	cin >> n >> m;
	d=0;
	child=0;
	memset(par,-1,sizeof(par));
	memset(num,-1,sizeof(num));
	memset(low,-1,sizeof(low));
	for(int i = 0; i < m; i++) {
		cin >> u >> v;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
	}
	dfs(0);
	for(int i = 0; i < n; i++) {
		cout << i << " " << pigeon[i] << endl;
	}
}
