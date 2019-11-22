#include <bits/stdc++.h>

using namespace std;

struct qwer {
    int l,r,idx;
};

int n,q,arr[30005],cnt[1000005],m,le,ri,ret[200005],ans=0;
qwer qq[200005];

bool compare(qwer a,qwer b) {
    if((a.l/m)!=(b.l/m))
        return (a.l/m)<(b.l/m);
    if((a.l/m)&1)
    	return a.r>b.r;
    return a.r<b.r;
}

int main() {
	cin>>n;
	m=sqrt(n);
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
	}
	cin>>q;
	for(int i=0;i<q;i++) {
		cin>>le>>ri;
		qq[i].l=le-1;
		qq[i].r=ri-1;
		qq[i].idx=i;
	}
	sort(qq,qq+q,compare);
	int mole=0, mori=-1;
	for(int i=0;i<q;i++) {
		int left=qq[i].l, right=qq[i].r;
		while(mori<right) {
			mori++;
			if(cnt[arr[mori]]==0) {
				ans++;
			}
			cnt[arr[mori]]++;
		}
		while(mori>right) {
			cnt[arr[mori]]--;
			if(cnt[arr[mori]]==0) {
				ans--;
			}
			mori--;
		}
		while(mole>left) {
			mole--;
			if(cnt[arr[mole]]==0) {
				ans++;
			}
			cnt[arr[mole]]++;
		}
		while(mole<left) {
			cnt[arr[mole]]--;
			if(cnt[arr[mole]]==0) {
				ans--;
			}
			mole++;
		}
		ret[qq[i].idx]=ans;
	}
	for(int i=0;i<q;i++) {
		printf("%d\n",ret[i]);
	}
}
