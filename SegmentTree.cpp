//Topic: Segment Tree + Lazy Propagation
//Query: Sum of range
//Updates: addition

#include <bits/stdc++.h>
using namespace std;

int n, a[100010], q, tree[4 * 100010], lazy[4 * 100010], lf, rg, v, type;

void init(int now, int l, int r, int val) {
	tree[now] += (r - l + 1) * val;
    if(l != r){
        lazy[now * 2] += val;
        lazy[now * 2 + 1] += val;
    }
}

void dropdown(int now, int l, int r) {
	if(lazy[now] != 0) {
		tree[now] += (r - l + 1) * lazy[now];
        if(l!=r) {
            lazy[now * 2] += lazy[now];
            lazy[now * 2 + 1] += lazy[now];
        }
        lazy[now] = 0;
	}
}

void build(int now, int l, int r) {
	if(l == r) {
		tree[now] = a[l];
		return;
	}
	int m = (l + r) / 2;
	build(now * 2, l, m);
	build(now * 2 + 1, m + 1, r);
	tree[now] = tree[now * 2] + tree[now * 2 + 1];
}

void update(int now, int l, int r, int st, int en, int val) {
	dropdown(now, l, r);
	if(en < l || r < st) {
		return;
	}
	if(st <= l && r <= en){
        init(now, l, r ,val);
        return;
    }
    int m = (l + r) / 2;
    update(now * 2, l, m, st, en, val);
    update(now * 2 + 1, m + 1, r, st, en, val);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
}

int query(int now, int l, int r, int st, int en) {
	if(en < l || r < st) {
		return 0;
	}
	dropdown(now, l, r);
	if(st <= l && r <= en) {
		return tree[now];
	}
	int m = (l + r) / 2;
	int ret = query(now * 2, l, m, st, en) + query(now * 2 + 1, m + 1, r, st, en);
    return ret;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	memset(lazy, 0, sizeof(lazy));
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, 1, n);
	for(int i = 1; i <= q; i++) {
		cin >> type;
		if(type == 0) { //update
			cin >> lf >> rg >> v;
			update(1, 1, n, lf, rg, v);
		}
		else { //query
			cin >> lf >> rg;
			cout << query(1, 1, n, lf, rg) << endl;
		}
	}
	return 0;
}
