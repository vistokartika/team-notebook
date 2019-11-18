//Segment Tree + Lazy Propagation for RMQ with additional updates

#include <bits/stdc++.h>
using namespace std;

long long n, a[200010], q, tree[4 * 200010], lazy[4 * 200010], inf = 1e18 + 10, lf, rg, v;

void build(int now, int l, int r) {
	if(l == r) {
		tree[now] = a[l];
		return;
	}
	int m = (l + r) / 2;
	build(now * 2, l, m);
	build(now * 2 + 1, m + 1, r);
	tree[now] = min(tree[now * 2], tree[now * 2 + 1]);
}

void update(int now, int l, int r, int st, int en, int val) {
	// drop down
	if(lazy[now] != 0) {
		tree[now] += lazy[now];
        if(l!=r) {
            lazy[now * 2] += lazy[now];
            lazy[now * 2 + 1] += lazy[now];
        }
        lazy[now] = 0;
	}
	if(en < l || r < st) {
		return;
	}
	//initialize drop down
	if(st <= l && r <= en){
        tree[now] += val;
        if(l != r){
            lazy[now * 2] += val;
            lazy[now * 2 + 1] += val;
        }
        return;
    }
    int m = (l + r) / 2;
    update(now * 2, l, m, st, en, val);
    update(now * 2 + 1, m + 1, r, st, en, val);
    tree[now] = min(tree[now * 2], tree[now * 2 + 1]);
}

long long query(int now, int l, int r, int st, int en) {
	if(en < l || r < st) {
		return inf;
	}
	//drop down
	if(lazy[now] != 0) {
		tree[now] += lazy[now];
        if(l!=r) {
            lazy[now * 2] += lazy[now];
            lazy[now * 2 + 1] += lazy[now];
        }
        lazy[now] = 0;
	}
	if(st <= l && r <= en) {
		return tree[now];
	}
	int m = (l + r) / 2;
    return min(query(now * 2, l, m, st, en), query(now * 2 + 1, m + 1, r, st, en));
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	memset(lazy, 0, sizeof(lazy));
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, 1, n);
	cin >> q;
	for(int i = 1; i <= q; i++) {
		cin >> lf >> rg;
		lf++;
		rg++;
		if(cin.get() == 10) {
			if(lf <= rg) {
				cout << query(1, 1, n, lf, rg) << endl;
			}
			else {
				cout << min(query(1, 1, n, lf, n), query(1, 1, n, 1, rg)) << endl;
			}
		}
		else {
			cin >> v;
			if(lf <= rg) {
				update(1, 1, n, lf, rg, v);
			}
			else {
				update(1, 1, n, lf, n, v);
				update(1, 1, n, 1, rg, v);
			}
		}
	}
	return 0;
}
