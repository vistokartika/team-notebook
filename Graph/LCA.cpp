//Finding the lowest common ancestor of two vertices in a tree

const int GraphSize = 1000;
const int MaxLevel = 14;
vector<int> adjlist[GraphSize];
int depth[GraphSize];
int parent[GraphSize][MaxLevel];

void dfs(int front){
	int sz = adjlist[front].size();
	for(int i = 0; i < sz; i++){
		if(parent[adjlist[front][i]][0] == -1){
			parent[adjlist[front][i]][0] = front;
			depth[adjlist[front][i]] = depth[front] + 1;
			dfs(adjlist[front][i]);
		}
	}
}

void precompute(int v, int start){
	memset(parent, -1, sizeof(parent));
	depth[start] = 0;
	dfs(start);
	for(int i = 1; i < MaxLevel; i++){
		for(int j = 1; j <= v; j++){
			if(parent[j][i-1] != -1){
				parent[j][i] = parent[parent[j][i-1]][i-1];
			}
		}
	}
}

int lca(int x, int y){
	if(depth[y] < depth[x]){
		swap(x, y);
	}

	int diff = depth[y] - depth[x];
	for(int i = 0; i < MaxLevel; i++){
		if((diff >> i) & 1){
			y = parent[y][i];
		}
	}

	if(y == x)
		return y;

	for(int i = MaxLevel-1; i >= 0; i--){
		if(parent[y][i] != parent[x][i]){
			y = parent[y][i];
			x = parent[x][i];
		}
	}

	return parent[x][0];
}

void solve(int v, int start, int x, int y){
	precompute(v, start);

	int LCA = lca(x, y);
}
