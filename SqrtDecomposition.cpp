#include <bits/stdc++.h>

using namespace std;

int asdf=0,n,arr[200005],m,block[505],idx,x,y;
string q;

void init() 
{ 
    idx = -1; 
    m = sqrt(n); 
    for (int i=0; i<n; i++) 
    { 
        if (i%m == 0) 
        { 
            idx++; 
        } 
        block[idx] += arr[i];
    } 
} 

void update(int idx, int val) 
{ 
    int num = idx / m; 
    block[num] += val - arr[idx]; 
    arr[idx] = val; 
}

int query(int l, int r) 
{ 
    int ret = 0; 
    while (l<r && l%m!=0 && l!=0) 
    { 
        ret += arr[l]; 
        l++; 
    } 
    while (l+m <= r) 
    { 
        ret += block[l/m]; 
        l += m; 
    } 
    while (l<=r) 
    { 
        ret += arr[l]; 
        l++; 
    } 
    return ret; 
} 

int main() {
	while(cin>>n) {
		if(n==0) {
			return 0;
		}
		memset(arr,0,sizeof(arr));
		memset(block,0,sizeof(block));
		for(int i=0;i<n;i++) {
			cin>>arr[i];
		}
		init();
		asdf++;
		if(asdf>1) {
			cout<<endl;
		}
		cout<<"Case "<<asdf<<":"<<endl;
		while(cin>>q) {
			if(q=="END") {
				break;
			}
			else if(q=="M") {
				cin>>x>>y;
				x--;
				y--;
				cout<<query(x,y)<<endl;
			}
			else if(q=="S") {
				cin>>x>>y;
				x--;
				update(x,y);
			}
		}
	}
}
