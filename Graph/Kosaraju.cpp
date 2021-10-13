//Finding the strongly connected components on general graph

int n, m;
const int GraphSize = 1000;
vector<int> adjlist[GraphSize];
vector<int> inverted[GraphSize];
int visited[GraphSize];
int sccnum[GraphSize];
stack<int> st;

void dfs(int front){
	visited[front] = 1;
	int sz = adjlist[front].size();
	for(int i = 0; i < sz; i++){
		if(visited[adjlist[front][i]] == 0){
			dfs(adjlist[front][i]);
		}
	}
	st.push(front);
}

void findscc(){
	memset(sccnum, 0, sizeof(sccnum));
	int top, front, sz, num = 1;
	queue<int> q;
	while(st.empty() == false){
		top = st.top();
		st.pop();
		if(sccnum[top] != 0)
			continue;
		sccnum[top] = num;
		q.push(top);
		while(q.empty() == false){
			front = q.front();
			q.pop();
			sz = inverted[front].size();
			for(int i = 0; i < sz; i++){
				if(sccnum[inverted[front][i]] == 0){
					sccnum[inverted[front][i]] = num;
					q.push(inverted[front][i]);
				}
			}
		}
		num++;
	}
}

void solve(){
	memset(visited, 0, sizeof(visited));
	for(int i = 1 ; i <= n ; i++) if(visited[i] == false) dfs(i);
	findscc();
}
