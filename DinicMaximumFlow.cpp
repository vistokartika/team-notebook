#include <bits/stdc++.h>
using namespace std;
const int msz = 5005;

struct Edges{
	int u, v;
	long long cap, flow;
	Edges(){}
	Edges(int u, int v, long long cap): u(u), v(v), cap(cap), flow(0) {}
};

vector<Edges> edgelist;
vector<int> adjlist[msz];
int depth[msz], pt[msz], n, m;

void addedge(int u, int v, long long cap){
	Edges A(u, v, cap);
	edgelist.push_back(A);
	adjlist[u].push_back(edgelist.size() - 1);
	Edges B(v, u, 0);
	edgelist.push_back(B);
	adjlist[v].push_back(edgelist.size() - 1);
}

bool bfs(int s, int t){
	fill(depth, depth + msz, msz);
	queue<int> q;
	q.push(s);
	depth[s] = 0;
	while(q.empty() == false){
		int front = q.front();
		q.pop();
		if(front == t) break;
		int sz = adjlist[front].size();
		for(int i = 0; i < sz; i++){
			Edges a = edgelist[adjlist[front][i]];
			if(a.flow < a.cap && depth[a.v] > depth[a.u] + 1){
				depth[a.v] = depth[a.u] + 1;
				q.push(a.v);
			}
		}
	}
	return depth[t] != msz;
}

long long dfs(int s, int t, long long flow = -1){
	if(s == t || flow == 0){
		return flow;
	}
	int push, augment;
	int sz = adjlist[s].size();
	for(int &i = pt[s]; i < sz; i++){
		Edges &front = edgelist[adjlist[s][i]];
		Edges &back = edgelist[adjlist[s][i]^1];
		if(depth[front.v] == depth[front.u] + 1){
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
		fill(pt, pt + msz, 0);
		while(long long flow = dfs(s, t))
			ret += flow;
	}
	return ret;
}

int main(){
	cin >> n >> m;
	for(long long i=0;i<m;i++) {
		int u, v, c;
		cin >> u >> v >> c;
		addedge(u, v, c);
		addedge(v, u, c);
	}
    cout << dinic(1, n) <<endl;
	return 0;
}
