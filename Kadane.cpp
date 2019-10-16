#include<bits/stdc++.h>

int a[1000],n;
int kadane(){
    int mx = 0;
    int mx_current = 0;
    for(int i=1;i<=n;i++){
        mx_current += a[i];
        mx = max(mx,mx_current);
        mx_current = max(mx_current,0);
    }
    return mx;
}
int main(){

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    cout<<kadane()<<endl;

}
