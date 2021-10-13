//All indexing starts at 1
//1D Fenwick
void update(int pos, int delta){
    while(pos <= n){
        bit[pos] += delta;
        pos += (pos & -pos);
    }
}

int query(int pos){
    int ret = 0;
    while(pos >= 1){
        ret += bit[pos];
        pos -= (pos & -pos);
    }
    return ret;
}

/*
    Range Update
    update(a, b, c): from range a to b inclusive add c
        update(BIT1, a, c), update(BIT1, b+1, -c)
        update(BIT2, a, -c*(a-1)), update(BIT2, b+1, c*b)

    query(x)
        query(BIT1, x) * x + query(BIT2, x)
*/

//2D Fenwick
void update(int x, int y, int delta){
    while(x <= n){
        while(y <= m){
            bit[x][y] += delta;
            y += (y & -y);
        }
        x += (x & -x);
    }
}

int query(int x, int y){
    int ret = 0;
    while(x >= 1){
        while(y >= 1){
            ret += bit[x][y];
            y += (y & -y);
        }
        x += (x & -x);
    }
    return ret;
}
