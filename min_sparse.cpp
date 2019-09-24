#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef string str;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector <pii> vpii;
typedef vector <pll> vpll;
typedef map <str,int> mapsi;
typedef map <str,int> :: iterator mapsitr;
typedef map <int , int> mint;
typedef map <ll , ll> mll;
typedef set <int> si;
typedef set <ll> sll;
typedef si :: iterator sitr;
typedef si :: reverse_iterator rsitr;
typedef sll :: iterator sltr;
typedef sll :: reverse_iterator rsltr;
#define mset multiset
typedef mset <int> msi;
typedef mset <ll> msll;
typedef msi :: iterator msitr;
typedef msi :: reverse_iterator msritr;
typedef msll :: iterator msltr;
typedef msll :: reverse_iterator mslritr;
#define mp make_pair
#define pb push_back
#define pob pop_back
#define fi first
#define se second
#define fs first.second
#define ss second.second
#define ff first.first
#define sf second.first
#define newl '\n'
char to_upper (char x){
    if( 97 <= int(x) && int(x) <= 126)return char(x-32);
    else if( 65 <= int(x) && int(x) <= 90)return x;
}
char to_lower (char x){
    if( 97 <= int(x) && int(x) <= 126)return x;
    else if( 65 <= int(x) && int(x) <= 90)return char(x+32);
}
int numerize (char x){
    if(48 <= int(x) && int(x) <= 57)return int(x-'0');
    else if( 97 <= int(x) && int(x) <= 126)return int(x-96);
    else if( 65 <= int(x) && int(x) <= 90)return int(x-64);
}
//void IO(){
//	#ifndef ONLINE_JUDGE
//	    freopen("input.txt", "r", stdin);
//	    freopen("output.txt", "w", stdout);
//	#endif
//}
// end of Template

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
	//IO();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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

    cout<<mini(1,5)<<newl;

//    SAMPLE INPUT
//    6
//    3 2 7 4 5 1
//    SAMPLE OUTPUT
//    2

}
