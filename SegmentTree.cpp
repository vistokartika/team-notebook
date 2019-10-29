#include <bits/stdc++.h>

using namespace std;

long long t,n,m,a[100005],q,x,y,tree[4*100005],lazy[4*100005],st,en;

void build(long long now, long long l, long long r)
{
    if(l==r)
    {
        tree[now]=a[l];
        return;
    }
    long long m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    tree[now]=tree[now*2]+tree[now*2+1];
}

void update_range(long long now, long long l, long long r, long long s, long long e, long long val)
{
    if(lazy[now]!=0)
    {
        tree[now]+=(r-l+1)*lazy[now];
        if(l!=r)
        {
            lazy[now*2]+=lazy[now];
            lazy[now*2+1]+=lazy[now];
        }
        lazy[now]=0;
    }
    if(r<s || e<l)
        return;
    if(s<=l && r<=e)
    {
        tree[now] += (r-l+1)*val;
        if(l!=r)
        {
            lazy[now*2] += val;
            lazy[now*2+1] += val;
        }
        return;
    }
    long long m=(l+r)/2;
    update_range(now*2,l,m,s,e,val);
    update_range(now*2+1,m+1,r,s,e,val);
    tree[now]=tree[now*2]+tree[now*2+1];
}

long long query_range(long long now, long long l, long long r, long long x, long long y)
{
    if(y<l || r<x)
        return 0;
    if(lazy[now]!=0)
    {
        tree[now]+=(r-l+1)*lazy[now];
        if(l!=r)
        {
            lazy[now*2]+=lazy[now];
            lazy[now*2+1]+=lazy[now];
        }
        lazy[now]=0;
    }
    if(x<=l && r<=y)
        return tree[now];
    long long m=(l+r)/2;
    return query_range(now*2,l,m,x,y)+query_range(now*2+1,m+1,r,x,y);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>t;
	for(long long asdf=1;asdf<=t;asdf++) {	
		memset(lazy,0,sizeof(lazy));
		memset(tree,0,sizeof(tree));
		memset(a,0,sizeof(a));
	    cin>>n>>m;
	    build(1,1,n);
	    for(long long i=0;i<m;i++)
	    {
	        cin>>q;
	        if(q==1)
	        {
	            cin>>x>>y;
	            cout<<query_range(1,1,n,x,y)<<endl;
	        }
	        else if(q==0)
	        {
	            cin>>st>>en>>y;
	            update_range(1,1,n,st,en,y);
	        }
	    }
	}
}
