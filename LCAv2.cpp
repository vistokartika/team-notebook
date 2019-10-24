#include<bits/stdc++.h>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

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
#define pf push_front
#define pof pop_front
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
bool isect (int l1, int r1, int l2, int r2){
    pii p1,p2;
    p1 = mp(l1,r1); p2 = mp(l2,r2);
    if(p1>p2)swap(p1,p2);
    if(p2.fi <= p1.se)return true;
    else return false;
}
ll fexp (ll num1, ll num2, ll MOD){
    if(num2==0)return 1;
    else if(num2==1)return num1;
    else{
        ll temp = fexp (num1,num2/2,MOD); ll res = ((temp%MOD) * (temp%MOD))%MOD;
        if(num2%2==1) res = ((res%MOD)*(num1%MOD))%MOD; return res;
    }
}
ll invmod (ll num, ll MOD){return fexp (num,MOD-2,MOD);}
ll gcd (ll num1, ll num2){
    if(num1 < num2) swap(num1,num2); ll num3 = num1 % num2 ;
    while(num3 > 0){ num1 = num2; num2 = num3; num3 = num1 % num2;}
    return num2;
}
ll lcm (ll num1 , ll num2){return (ll) (num1/gcd(num1,num2))*num2;}
// end of Template

int n;
ll dua[30];
vi adj[100010];
bool vis[100010];
bool vist[100010];
int depth[100010];
int parent[100010][30];
void build_parent(){
	queue <int> q;
	q.push(1);

	while(!q.empty()){
		int node = q.front();
		q.pop();
		if(!vis[node]){
			vis[node] = true;
			for(int i=0;i<adj[node].size();i++){
				int nex = adj[node][i];
				if(!vis[nex]){
					parent[0][nex] = node;
					q.push(nex);
				}
			}

		}
	}
	for(int i=1;i<=(log(n)/log(2));i++){
		for(int j=1;j<=n;j++){
			parent[i][j] = parent[i-1][parent[i-1][j]];
		}
	}
}
void build_depth(){
	queue <pii> q;
	q.push(mp(1,1));
	while(!q.empty()){
		int node = q.front().fi;
		int steps = q.front().se;
		q.pop();
		if(!vist[node]){
			vist[node] = true;
			depth[node] = steps;
			for(int i=0;i<adj[node].size();i++){
				int nex = adj[node][i];
				q.push(mp(nex,steps+1));
			}

		}
	}
}
pii lift(pii p, int maxn){
	int a,b; a=p.fi; b=p.se;
	for(int i=maxn;i>=0;i--){
		if(parent[i][a] != parent[i][b]){
			a = parent[i][a];
			b = parent[i][b];
			return lift(mp(a,b),i);
		}
	}
	return p;
}
int lca(int a, int b){
	if(depth[a] > depth[b])swap(a,b);

	if(depth[a] != depth[b]){
		int x = abs(depth[a]-depth[b]);
		queue <int> temp;
		while(x>0){
			temp.push(x%2);
			x/=2;
		}
		int idx = 0;
		while(!temp.empty()){
			int f = temp.front();
			temp.pop();
			if(f){b = parent[idx][b];}
			idx++;
		}
	}


	int ans = a;
	if(a!=b){
		pii res = lift(mp(a,b),log(n)/log(2));
		ans = parent[0][res.fi];
	}
	return ans;
}
int q;
int main(){

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

 	// root = 1;

	 dua[0] = 1;
	 for(int i=1;i<30;i++)dua[i] = dua[i-1] * 2;

	cin>>n;
 	for(int i=1;i<n;i++){
 		int u,v; cin>>u>>v;
	 	adj[u].pb(v);
	 	adj[v].pb(u);
	}

	build_parent();
	build_depth();

	cin>>q;
	for(int i=1;i<=q;i++){
		int u,v; cin>>u>>v;
		cout<<lca(u,v)<<newl;
	}

}
