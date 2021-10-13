// Complexity: O(V^2 E^2)
const int INF = (int)1e9+7, MAXN = 405;
int SRC, SINK;
int flow, costperflow, maxflow, totalcost;
int res[MAXN][MAXN], cost[MAXN][MAXN], dist[MAXN], p[MAXN];
vector<int> adj[MAXN];

bool bellman() { // O(VE)
    for (int i = SRC; i <= SINK; i++) {
        dist[i] = INF;
        p[i] = -1;
    }  
    dist[SRC] = 0;
    queue<int> q;
    q.push(SRC);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i], w = cost[u][v];
            if (dist[v] > dist[u] + w && res[u][v] > 0) {
                p[v] = u;
                dist[v] = dist[u]+w;
                q.push(v);
    }}}
    return dist[SINK] != INF;
}

void augment(int u, int minedge) {
    if (u == SRC) { flow = minedge; return; }
    else if (p[u] != -1) {
        augment(p[u], min(minedge, res[p[u]][u]));
        res[p[u]][u] -= flow;
        res[u][p[u]] += flow;
        costperflow += cost[p[u]][u];
}}

int main() {
    // foreach edge {
        adj[u].pb(v); adj[v].pb(u);
        res[u][v] = 1; res[v][u] = 0;
        cost[u][v] = c; cost[v][u] = -c;
    }
    totalcost = 0, maxflow = 0;
    while (bellman()) {
        flow = 0; costperflow = 0;
        augment(SINK, INF);
        totalcost += costperflow;
        maxflow += flow;
    }
    printf("maxflow=%d, totalcost=%d\n", maxflow, totalcost);
}
