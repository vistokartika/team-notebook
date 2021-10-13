//Finding the single source shortest path and detecting negative cycle

const int GraphSize = 1000;
const int INF = 100000000;
vector<pair<int, int>> adjlist[GraphSize];
int dist[GraphSize];

bool bellmanford(int start, int n){
	fill(dist, dist+GraphSize, INF);
	dist[start] = 0;
	int sz;
	for(int k = 0; k < n; k++){
		if(dist[k] == INF){
			continue;
		}
		sz = adjlist[k].size();
		for(int i = 0; i < sz; i++){
			dist[adjlist[k][i].first] = min(dist[adjlist[k][i].first], dist[k] + adjlist[k][i].second);
		}
	}
	
	for(int k = 0; k < n; k++){
		sz = adjlist[k].size();
		for(int i = 0; i < sz; i++){
			if(dist[k] + adjlist[k][i].second < dist[adjlist[k][i].first]){
				return true;
			}
		}
	}
	return false;
}

void solve(int start, int n){
	//generate distance from start to all vertices and check if there's negative cycle
	bool negative = bellmanford(start, n);
}
