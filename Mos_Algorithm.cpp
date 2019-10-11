#include <bits/stdc++.h>

using namespace std;

struct query {
    int l, r, idx;
};

const int MSIZE = 100010;
int n, m, q, le, ri;
int arr[MSIZE], ret[MSIZE];
query qq[MSIZE];

bool compare(query a, query b) {
    if((a.l / m) != (b.l / m))
        return (a.l / m) < (b.l / m);
    else
    	return a.r <  b.r;
}

void init() {
	cin>>n>>q;
	m=sqrt(n);
	for(int i=0;i<n;i++)
		cin >> arr[i];
	for(int i=0;i<q;i++) {
		cin >> le >> ri;
		qq[i].l=--le;
		qq[i].r=--ri;
		qq[i].idx=i;
	}
}

void mo() {
	sort(qq, qq + q, compare);
	int ans = 0, mole = 0, mori = -1;
	for(int i = 0; i < q; i++) {
		int left = qq[i].l, right = qq[i].r;
		while(mori<right) {
			mori++;
			ans += arr[mori];
		}
		while(mori>right) {
			ans -= arr[mori];
			mori--;
		}
		while(mole>left) {
			mole--;
			ans += arr[mole];
		}
		while(mole<left) {
			ans -= arr[mole];
			mole++;
		}
		ret[qq[i].idx] = ans;
	}
}

void out() {
	for(int i = 0; i < q; i++) {
		cout << ret[i] << endl;
	}
}

void solve() {
	init();
	mo();
	out();
}

int main() {
	solve();
}
