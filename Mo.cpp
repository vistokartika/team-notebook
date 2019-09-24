#include <bits/stdc++.h>

using namespace std;

struct qwer {
    long long l,r,idx;
};

long long n,q,arr[200005],cnt[1000005],m,le,ri,ret[200005],ans=0;
qwer qq[200005];

bool compare(qwer a,qwer b) {
    if((a.l/m)!=(b.l/m))
        return (a.l/m)<(b.l/m);
    else
    	return a.r<b.r;
}

int main() {
	cin>>n>>q;
	m=sqrt(n);
	for(long long i=0;i<n;i++) {
		scanf("%I64d",&arr[i]);
	}
	for(long long i=0;i<q;i++) {
		scanf("%I64d %I64d",&le,&ri);
		qq[i].l=le-1;
		qq[i].r=ri-1;
		qq[i].idx=i;
	}
	stable_sort(qq,qq+q,compare);
	long long mole=0, mori=-1;
	for(long long i=0;i<q;i++) {
		long long left=qq[i].l, right=qq[i].r;
		while(mori<right) {
			mori++;
			ans-=(cnt[arr[mori]]*cnt[arr[mori]]*arr[mori]);
			cnt[arr[mori]]++;
			ans+=(cnt[arr[mori]]*cnt[arr[mori]]*arr[mori]);
		}
		while(mori>right) {
			ans-=(cnt[arr[mori]]*cnt[arr[mori]]*arr[mori]);
			cnt[arr[mori]]--;
			ans+=(cnt[arr[mori]]*cnt[arr[mori]]*arr[mori]);
			mori--;
		}
		while(mole>left) {
			mole--;
			ans-=(cnt[arr[mole]]*cnt[arr[mole]]*arr[mole]);
			cnt[arr[mole]]++;
			ans+=(cnt[arr[mole]]*cnt[arr[mole]]*arr[mole]);
		}
		while(mole<left) {
			ans-=(cnt[arr[mole]]*cnt[arr[mole]]*arr[mole]);
			cnt[arr[mole]]--;
			ans+=(cnt[arr[mole]]*cnt[arr[mole]]*arr[mole]);
			mole++;
		}
		ret[qq[i].idx]=ans;
	}
	for(long long i=0;i<q;i++) {
		printf("%I64d\n",ret[i]);
	}
}
