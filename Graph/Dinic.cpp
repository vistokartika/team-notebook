//Finding the maximum flow of a flow graph

struct Edges{
	int u, v;
	long long cap, flow;

	Edges(){}
	Edges(int u, int v, long long cap): u(u), v(v), cap(cap), flow(0) {}
};

const int GraphSize = 1000;
vector<Edges> edgelist;
vector<int> adjlist[GraphSize];
int depth[GraphSize], pt[GraphSize];

void addedge(int u, int v, long long cap){
	Edges a(u, v, cap);
	edgelist.push_back(a);
	adjlist[u].push_back(edgelist.size()-1);
	Edges b(v, u, 0);
	edgelist.push_back(b);
	adjlist[v].push_back(edgelist.size()-1);
}

bool bfs(int s, int t){
	fill(depth, depth+GraphSize, 100000);
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
				q.push(a.v);
				depth[a.v] = depth[a.u] + 1;
			}
		}
	}
	return depth[t] != 100000;
}

long long dfs(int s, int t, long long flow = -1){
	if(s == t || flow == 0)
		return flow;
	long long augment, push;
	int sz = adjlist[s].size();
	for(int &i = pt[s]; i < sz; i++){
		Edges &front = edgelist[adjlist[s][i]];
		Edges &back = edgelist[adjlist[s][i]^1];
		if(depth[front.v] == depth[front.u] + 1){
			augment = front.cap - front.flow;
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

void solve(int s, int t){
	long long push, total = 0;
	while(bfs(s, t)){
		fill(pt, pt+GraphSize, 0);
		while(push = dfs(s, t)){
			total += push;
		}
	}
}
