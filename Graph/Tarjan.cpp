//Finding articulation points and bridges in a general graph

const int GraphSize = 1000;
int root, child, counter;
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

void solve(int v){
	//v is the number of vertices
	counter = 0;
	memset(num, -1, sizeof(num));
	memset(low, 0, sizeof(low));
	for(int i = 0; i < v; i++){
		if(num[i] == -1){
			root = i;
			child = 0;
			tarjan(i);
			if(child > 1)
				artpoint[i] = true;
		}
	}
}
