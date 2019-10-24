const int MSIZE = 1000;
vector<pair<int, int>> adjlist[MSIZE];
int chainhead[MSIZE], chainidx[MSIZE], pos[MSIZE];
int parent[MSIZE], basearr[MSIZE], subsize[MSIZE];
int ptr, chainno;
void hld(int cur, int cost, int prev){
	if(chainhead[chainno] == -1) chainhead[chainno] = cur;
	chainidx[cur] = chainno;
	pos[cur] = ptr; basearr[ptr] = cost; ptr++;
	int nextcost, nextchild = -1; int sz = adjlist[cur].size();
	for(int i = 0; i < sz; i++){
		if(adjlist[cur][i].first == prev) continue;
		if(nextchild == -1 || subsize[nextchild] < subsize[adjlist[cur][i].first]){
			nextchild = adjlist[cur][i].first;
			nextcost = adjlist[cur][i].second;
		}
	}
	if(nextchild != -1) hld(nextchild, nextcost, cur);
	for(int i = 0; i < sz; i++){
		if(adjlist[cur][i].first == prev || adjlist[cur][i].first == nextchild) continue;
		chainno++; hld(adjlist[cur][i].first, adjlist[cur][i].second, cur);
	}
}
void dfs(int cur, int prev){
	subsize[cur] = 1; int sz = adjlist[cur].size();
	for(int i = 0; i < sz; i++){
		if(adjlist[cur][i].first == prev)
			continue;
		parent[adjlist[cur][i].first] == cur;
		dfs(adjlist[cur][i].first, cur);
		subsize[cur] += subsize[adjlist[cur][i].first];
	}
}
int query(int u, int v){
	if(u == v) return 0;
	int uchain, vchain, ans;
	vchain = chainidx[v]; ans = -1;
	while(true){
		uchain = chainidx[u];
		if(uchain == vchain){
			if(u == v) break;
			//query on tree operation depends on the problem description
			//querytree(1, 0, ptr, chainpos[v]+1, chainpos[u]+1);
			break;
		}
		//query on tree operation depends on the problem description
		//querytree(1, 0, ptr, chainpos[chainhead[uchain]], chainpos[u]+1);
		u = chainhead[uchain]; u = parent[u];
	}
	return ans;	
}
void solve(int root, int u, int v){
	chainno = ptr = 0;
	dfs(root, -1); hld(root, -1, -1);
	int ans = query(u, v);
}
