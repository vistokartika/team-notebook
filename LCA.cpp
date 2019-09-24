#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005;
const int level = 10;

vector<int> adjlist[MAXN];
int depth[MAXN];
int parent[MAXN][level];

void dfs(int now, int par){
	depth[now] = depth[par] + 1;
	parent[now][0] = par;
	int sz = adjlist[now].size();
	for(int i = 0; i < sz; i++){
		if(adjlist[now][i] != par){
			dfs(adjlist[now][i], now);
		}
	}
}

void precompute(int n){
	for(int i = 1; i < level; i++){
		for(int j = 1; j <= n; j++){
			if(parent[j][i-1] != -1){
				parent[j][i] = parent[parent[j][i-1]][i-1];
			}
		}
	}
}

int lca(int u, int v){
	if(depth[v] < depth[u]){
		swap(u, v);
	}
	
	int diff = depth[v] - depth[u];
	for(int i = 0; i < level; i++){
		if((diff >> i) & 1){
			v = parent[v][i];
		}
	}
	
	if(u == v)
		return u;
		
	for(int i = level-1; i >= 0; i--){
		if(parent[u][i] != parent[v][i]){
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	
	return parent[u][0];
}

int main(){
	
	int n, a, b;
	cin >> n;
	for(int i = 0; i < n-1; i++){
		cin >> a >> b;
		adjlist[a].push_back(b);
		adjlist[b].push_back(a);
	}
	
	memset(parent, -1, sizeof(parent));
	depth[0] = 0;
	dfs(1, 0);
	precompute(n);
	
	int x, y;
	cin >> x >> y;
	cout << lca(x, y) << endl;
	return 0;
}
