#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MSIZE = 505;

struct Edges{
	int u, v;
	ll cap, flow;
	
	Edges(){}
	Edges(int u, int v, ll cap): u(u), v(v), cap(cap), flow(0) {}
};

vector<Edges> edgelist;
vector<int> adjlist[MSIZE];
int depth[MSIZE], pt[MSIZE], n, m, s, t, u, v, c, cnt = 0;

void addedge(int u, int v, ll cap){
	Edges A(u, v, cap);
	edgelist.push_back(A);
	adjlist[u].push_back(edgelist.size()-1);
	Edges B(v, u, 0);
	edgelist.push_back(B);
	adjlist[v].push_back(edgelist.size()-1);
}

bool bfs(int s, int t){
	fill(depth, depth+MSIZE, 100000);
	depth[s] = 0;
	queue<int> q;
	q.push(s);
	int front, sz;
	Edges a;
	while(q.empty() == false){
		front = q.front();
		q.pop();
		if(front == t)
			break;
		sz = adjlist[front].size();
		for(int i = 0; i < sz; i++){
			a = edgelist[adjlist[front][i]];
			if(a.flow < a.cap && depth[a.v] > depth[a.u] + 1){
				depth[a.v] = depth[a.u] + 1;
				q.push(a.v);
			}
		}
	}
	return depth[t] != 100000;
}

ll dfs(int s, int t, ll flow = -1){
	if(s == t || flow == 0){
		return flow;
	}
	ll push, augment;
	int sz = adjlist[s].size();
	for(int &i = pt[s]; i < sz; i++){
		Edges &front = edgelist[adjlist[s][i]];
		Edges &back = edgelist[adjlist[s][i]^1];
		if(depth[front.v] == depth[front.u]+1){
			augment = front.cap-front.flow;
			if(augment > flow && flow != -1){
				augment = flow;
			}
			if(push = dfs(front.v, t, augment)){
				front.flow += push;
				back.flow -= push;
				return push;
			}
		}
	}
	return 0;
}

long long dinic(long long s, long long t) {
	long long ret = 0;
	while(bfs(s, t)) {
		fill(pt, pt+MSIZE, 0);
		ret += dfs(s, t);
	}
	return ret;
}

int main(){
	cin>>n>>m>>s>>t;
	for(int i=0;i<m;i++) {
		cin>>u>>v>>c;
		addedge(u, v, c);
	}
	long long ans = dinic(s, t);
	for(int i=0;i<edgelist.size();i++) {
		if(edgelist[i].flow>0) {
			cnt++;
		}
	}
	cout<<n<<" "<<ans<<" "<<cnt<<endl;
	for(int i=0;i<edgelist.size();i++) {
		if(edgelist[i].flow>0) {
			cout<<edgelist[i].u<<" "<<edgelist[i].v<<" "<<edgelist[i].flow<<endl;
		}
	}
	return 0;
}
