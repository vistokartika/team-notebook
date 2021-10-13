//Finding topological sorting, counting number of ways and finding the longest or shortest path on DAG

const int GraphSize = 1000;
vector<int> sorted;
vector<pair<int, int>> adjlist[GraphSize];
int indeg[GraphSize];

void toposort(int v){
	queue<int> q;
	for(int i = 0; i < v; i++){
		if(indeg[i] == 0){
			q.push(i);
		}
	}

	int front, sz;
	while(q.empty() == false){
		front = q.front();
		q.pop();
		sorted.push_back(front);
		sz = adjlist[front].size();
		for(int i = 0; i < sz; i++){
			indeg[adjlist[front][i].first]--;
			if(indeg[adjlist[front][i].first] == 0){
				q.push(adjlist[front][i].first);
			}
		}
	}
}

long long countways(int v, int dest, int start){
	long long dp[v] = {0};
	dp[dest] = 1;
	int ssz, asz;
	ssz = sorted.size();
	for(int i = ssz-1; i >= 0; i--){
		asz = adjlist[sorted[i]].size();
		for(int j = 0; j < asz; j++){
			dp[sorted[i]] += dp[adjlist[sorted[i]][j].first];
		}
	}
	return dp[start];
}

long long findways(int v, int start){
	long long dist[v];
	fill(dist, dist+v, INT_MIN);
	//INT_MIN for finding shortest path
	dist[start] = 0;
	int ssz, asz;
	ssz = sorted.size();
	long long ans = INT_MIN;
	for(int i = 0; i < ssz; i++){
		asz = adjlist[sorted[i]].size();
		for(int j = 0; j < asz; j++){
			dist[adjlist[sorted[i]][j].first] = min(dist[adjlist[sorted[i]][j].first], dist[sorted[i]] + adjlist[sorted[i]][j].second);
			ans = max(ans, dist[adjlist[sorted[i]][j].first]);
		}
	}
	return ans;
}

void solve(int v, int dest, int start){
	sorted.clear();
	toposort(v);
	//sorted will contain the sorted vertices of the graph

	//count number of ways from source to sink
	int numways = countways(v, dest, start);

	//find the weight of the longest path in the DAG
	int pathlen = findways(v, start);
}
