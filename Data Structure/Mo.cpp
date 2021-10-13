//Efficient query operation

const int MSIZE = 100010;
int blocksz;
int arr[MSIZE], result[MSIZE];
query qq[MSIZE];

bool compare(query a, query b) {
    if((a.l / blocksz) != (b.l / blocksz))
        return (a.l / blocksz) < (b.l / blocksz);
    else
    	return a.r <  b.r;
}

void mo(int blocksz, int q){
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
		result[qq[i].idx] = ans;
	}
}

void solve(int n, int q){
	blocksz = sqrt(n);
	mo(blocksz, q);
}
