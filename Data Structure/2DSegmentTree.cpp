/* matrix a[0..n-1, 0..m-1] */
const int N = 1005, M = 1005;
int n, m, a[N][M], st[4*N][4*M];
void buildy(int px, int lx, int rx, int py, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) st[px][py] = a[lx][ly];
        else st[px][py] = st[px*2][py] + st[px*2+1][py];
    return;
    }
    int midy = (ly+ry)/2;
    buildy(px, lx, rx, py*2, ly, midy);
    buildy(px, lx, rx, py*2+1, midy, ry);
    st[px][py] = st[px][py*2] + st[px][py*2+1];
}

void buildx(int px, int lx, int rx) { // panggil ini di main to build(1, 0, n-1)
    if (lx != rx) {
        int midx = (lx+rx)/2;
        buildx(px*2, lx, midx);
        buildx(px*2+1, midx+1, rx);
    }
    buildy(px, lx, rx, 1, 0, m-1); // build a[l..r, 0..m-1]
}

void updatey(int px, int lx, int rx, int py, int ly, int ry, int x, int y, int val) {
    if (ly == ry) {
        if (lx == rx) st[px][py] = val;
        else st[px][py] = st[px*2][py] + st[px*2+1][py];
        return;
    }
    int midy = (ly+ry)/2;
    if (y &lt;= midy) updatey(px, lx, rx, py*2, ly, midy, x, y, val);
    else updatey(px, lx, rx, py*2+1, midy+1, ry, x, y, val);
    st[px][py] = st[px][py*2] + st[px][py*2+1];
}

void updatex(int px, int lx, int rx, int x, int y, int val) { //panggil update(1, 0, n-1, x, y, val)
    if (lx != rx) {
        int midx = (lx+rx)/2;
        if (x <= midx) updatex(px*2, lx, midx, x, y, val);
        else updatex(px*2+1, midx+1, rx, x, y, val);
    }
    updatey(px, lx, rx, 1, 0, m-1, x, y, val);
}

int sumy(int px, int py, int l, int r, int y1, int y2) {
    if (y2 < l || r < y1) return 0;
    if (y1 <= l && r <= y2) return st[px][py];
    int mid = (l+r)/2;
    return sumy(px, py*2, l, mid, y1, y2) + sumy(px, py*2+1, mid+1, r, y1, y2);
}

int sumx(int px, int l, int r, int x1, int x2, int y1, int y2) { // panggil sumx(1, 0, n-1, x1, x2, y1, y2)
    if (x2 < l || r < x1) return 0;
    if (x1 <= l && r <= x2) return sumy(px, 1, 0, m-1, y1, y2);

    int mid = (l+r)/2;
    return sumx(px*2, l, mid, x1, x2, y1, y2) +
    sumx(px*2+1, mid+1, r, x1, x2, y1, y2);
}
