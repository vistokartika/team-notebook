/********   All Required Header Files ********/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
#define SCD(t) scanf("%d",&t)
#define SCLD(t) scanf("%ld",&t)
#define SCLLD(t) scanf("%lld",&t)
#define SCC(t) scanf("%c",&t)
#define SCS(t) scanf("%s",t)
#define SCF(t) scanf("%f",&t)
#define SCLF(t) scanf("%lf",&t)
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define IN(A, B, C) assert( B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

/****** Template of some basic operations *****/
template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }
/**********************************************/

int n,m,a[100005],q,x,y,tree[4*100005],lazy[4*100005],st,en;

void build(int now, int l, int r)
{
    if(l==r)
    {
        tree[now]=a[l];
        return;
    }
    int m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    tree[now]=tree[now*2]+tree[now*2+1];
}

void update(int now, int l, int r, int pos, int val)
{
    if(l==r)
    {
        tree[now]=val;
        return;
    }
    int m=(l+r)/2;
    if(pos<=m)
        update(now*2,l,m,pos,val);
    else
        update(now*2+1,m+1,r,pos,val);
    tree[now]=tree[now*2]+tree[now*2+1];
}

void update_range(int now, int l, int r, int s, int e, int val)
{
    if(lazy[now]!=0)
    {
        tree[now]=(r-l+1)*lazy[now];
        if(l!=r)
        {
            lazy[now*2]=lazy[now];
            lazy[now*2+1]=lazy[now];
        }
        lazy[now]=0;
    }
    if(r<s || e<l)
        return;
    if(s<=l && r<=e)
    {
        tree[now] = (r - l + 1) * val;
        if(l!=r)
        {
            lazy[now*2] = val;
            lazy[now*2+1] = val;
        }
        return;
    }
    int m=(l+r)/2;
    update_range(now*2,l,m,s,e,val);
    update_range(now*2+1,m+1,r,s,e,val);
    tree[now]=tree[now*2]+tree[now*2+1];
}

int query(int now, int l, int r, int x, int y)
{
    if(x<=l && r<=y)
        return tree[now];
    if(y<l || r<x)
        return 0;
    int m=(l+r)/2;
    return query(now*2,l,m,x,y)+query(now*2+1,m+1,r,x,y);
}

int query_range(int now, int l, int r, int x, int y)
{
    if(y<l || r<x)
        return 0;
    if(lazy[now]!=0)
    {
        tree[now]=(r-l+1)*lazy[now];
        if(l!=r)
        {
            lazy[now*2]=lazy[now];
            lazy[now*2+1]=lazy[now];
        }
        lazy[now]=0;
    }
    if(x<=l && r<=y)
        return tree[now];
    int m=(l+r)/2;
    return query(now*2,l,m,x,y)+query(now*2+1,m+1,r,x,y);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    memset(lazy,0,sizeof(lazy));
    build(1,1,n);
    for(int i=0;i<m;i++)
    {
        cin>>q;
        if(q==0)
        {
            cin>>x>>y;
            cout<<query_range(1,1,n,x,y)<<endl;
        }
        else if(q==1)
        {
            cin>>st>>en>>y;
            update_range(1,1,n,st,en,y);
        }
    }
}
