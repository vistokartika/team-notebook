ll dua[30]; vi adj[100010];
bool vis[100010],vist[100010];
int n,q,depth[100010],parent[100010][30];
void build_parent(){
	queue <int> q; q.push(1);
	while(!q.empty()){
		int node = q.front(); q.pop();
		if(!vis[node]){
			vis[node] = true;
			for(int i=0;i<adj[node].size();i++){
				int nex = adj[node][i];
				if(!vis[nex]){
					parent[0][nex] = node; q.push(nex);
				}
			}
		}
	}
	for(int i=1;i<=(log(n)/log(2));i++){
		for(int j=1;j<=n;j++){
			parent[i][j] = parent[i-1][parent[i-1][j]];
		}
	}
}
void build_depth(){
	queue <pii> q;
	q.push(mp(1,1));
	while(!q.empty()){
		int node = q.front().fi; int steps = q.front().se;
		q.pop();
		if(!vist[node]){
			vist[node] = true;
			depth[node] = steps;
			for(int i=0;i<adj[node].size();i++){
				int nex = adj[node][i];
				q.push(mp(nex,steps+1));
			}
		}
	}
}
pii lift(pii p, int maxn){
	int a,b; a=p.fi; b=p.se;
	for(int i=maxn;i>=0;i--){
		if(parent[i][a] != parent[i][b]){
			a = parent[i][a];
			b = parent[i][b];
			return lift(mp(a,b),i);
		}
	}
	return p;
}
int lca(int a, int b){
	if(depth[a] > depth[b])swap(a,b);
	if(depth[a] != depth[b]){
		int x = abs(depth[a]-depth[b]);
		queue <int> temp;
		while(x>0){
			temp.push(x%2);
			x/=2;
		}
		int idx = 0;
		while(!temp.empty()){
			int f = temp.front();
			temp.pop();
			if(f){b = parent[idx][b];}
			idx++;
		}
	}
	int ans = a;
	if(a!=b){
		pii res = lift(mp(a,b),log(n)/log(2));
		ans = parent[0][res.fi];
	}
	return ans;
}
int main(){
 	// root = 1;
	dua[0] = 1; for(int i=1;i<30;i++)dua[i] = dua[i-1] * 2;
	// input tree
	build_parent();
	build_depth();
	// cout<<lca(u,v);
}
