int n,m,a[100005],q,x,y,tree[4*100005],lazy[4*100005],st,en;
void build(int now, int l, int r){
    if(l==r){
        tree[now]=a[l];
        return;
    }
    int m=(l+r)/2;
    build(now*2,l,m); build(now*2+1,m+1,r);
    tree[now]=tree[now*2]+tree[now*2+1];
}
void update(int now, int l, int r, int pos, int val)
{
    if(l==r){
        tree[now]=val;
        return;
    }
    int m=(l+r)/2;
    if(pos<=m) update(now*2,l,m,pos,val);
    else update(now*2+1,m+1,r,pos,val);
    tree[now]=tree[now*2]+tree[now*2+1];
}
void update_range(int now, int l, int r, int s, int e, int val)
{
    if(lazy[now]!=0){
        tree[now]=(r-l+1)*lazy[now];
        if(l!=r){
            lazy[now*2]=lazy[now];
            lazy[now*2+1]=lazy[now];
        }
        lazy[now]=0;
    }
    if(r<s || e<l) return;
    if(s<=l && r<=e){
        tree[now] = (r - l + 1) * val;
        if(l!=r){
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
int query(int now, int l, int r, int x, int y){
    if(x<=l && r<=y) return tree[now];
    if(y<l || r<x) return 0;
    int m=(l+r)/2; return query(now*2,l,m,x,y)+query(now*2+1,m+1,r,x,y);
}
int query_range(int now, int l, int r, int x, int y){
    if(y<l || r<x) return 0;
    if(lazy[now]!=0){
        tree[now]=(r-l+1)*lazy[now];
        if(l!=r){
            lazy[now*2]=lazy[now];
            lazy[now*2+1]=lazy[now];
        }
        lazy[now]=0;
    }
    if(x<=l && r<=y) return tree[now];
    int m=(l+r)/2;
    return query(now*2,l,m,x,y)+query(now*2+1,m+1,r,x,y);
}
int main(){

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(lazy,0,sizeof(lazy));
    build(1,1,n);
    for(int i=0;i<m;i++){
        cin>>q;
        if(q==0){
            cin>>x>>y; cout<<query_range(1,1,n,x,y)<<endl;
        }
        else if(q==1){
            cin>>st>>en>>y;
            update_range(1,1,n,st,en,y);
        }
    }
}
