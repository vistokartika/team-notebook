const int MSIZE = 1e5 + 10;
vector<int> parent, depth, heavy, head, pos, adjlist[MSIZE];
int cur_pos;

int dfs(int v){
    int size = 1;
    int max_c_size = 0;
    for(int c : adjlist[v]){
        if(c != parent[v]){
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c);
            size += c_size;
            if(c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return size;
}

int decompose(int v, int h){
    head[v] = h, pos[v] = cur_pos++;
    if(heavy[v] != -1)
        decompose(heavy[v], h, adj);
    for(int c : adjlist[v]){
        if (c != parent[v] && c != heavy[v])
            decompose(c, c);
    }
}

int query(int a, int b){ //find maximum on path a to b
    int res = 0;
    for(; head[a] != head[b]; b = parent[head[b]]){
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]); //create a segment tree DONT FORGET!!!
        res = max(res, cur_heavy_path_max);
    }
    if(depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}

void solve(){
    int n = adj.size();
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    cur_pos = 0;

    dfs(0, adj);
    decompose(0, 0, adj);
    int ans = query(0, 5);
}
