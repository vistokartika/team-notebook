// O(VE) 0 based-index
const ll INF = 1000000000;
vector<vector<pair<ll, ll>>> adj;

bool spfa(ll s, vector<ll>& dist) {
    ll n = adj.size();
    dist.assign(n, INF);
    vector<ll> cnt(n, 0);
    vector<bool> in(n, false);
    queue<ll> q;

    dist[s] = 0;
    q.push(s);
    in[s] = true;
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        in[v] = false;

        for (auto edge : adj[v]) {
            ll to = edge.first;
            ll len = edge.second;

            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                if (!in[to]) {
                    q.push(to);
                    in[to] = true;
                    cnt[to]++;
                    if (cnt[to] > n)
                        return false;  // negative cycle
                }
            }
        }
    }
    return true;
}
