#include<bits/stdc++.h>

int sparse[30][200000],a[200000];
int dua[30],n;
int mini (int l, int r){
    int range = r-l+1;
    // assign level to the closest 2^x which is <= range
    int lv = log(range)/log(2);
    int mn = min (sparse[lv][l],sparse[lv][r-dua[lv]+1]);
    return mn;
}
int main(){

    dua[0]=1;
    for(int i=1;i<=28;i++)dua[i]=dua[i-1]*2;

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sparse[0][i]=a[i];
    }
    // this is a min sparse
    for(int i=1;i<=log(n)/log(2);i++){
        // i is table level (lv)
        for(int j=1;j<=n;j++){
            // j is table index (idx)
            if(j+dua[i]-1<=n){
                sparse[i][j] = min (sparse[i-1][j] , sparse[i-1][j+dua[i-1]]);
            }
            else break;
        }
    }

    cout<<mini(1,5)<<endl;

}
