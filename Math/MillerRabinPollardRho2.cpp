#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define pob pop_back
#define mp make_pair
#define REPP(i,l,r,c) for (ll i=l;i<r;i+=c)
#define REP(i,l,r) REPP(i,l,r,1)
#define REPS(i,l,r) REP(i,l,r+1)
#define FOR(i,n) REP(i,0,n)
#define REPD(i,l,r) for (ll i=r-1;i>=l;i--)
#define FORD(i,n) REPD(i,0,n)
#define FOREACH(i,n) for (auto i:n)
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pii;

const ll MAXN = 1005;
vector<ll> prime, fact;
map<ll, ll> ans;
ll n;

void sieve(ll n)
{
    bool pr[n + 5];
    memset(pr, true, sizeof(pr));
 
    for (ll p = 2; p * p <= n; p++)
    {
        if (pr[p] == true) 
        {
            for (ll i = p * p; i <= n; i += p)
                pr[i] = false;
        }
    }

    for (ll p = 2; p <= n; p++)
        if (pr[p])
            prime.push_back(p);
}

ll mul(ll a, ll b, ll mod) { 
    ll ret=0; 
    for (a%=mod,b%=mod;b!=0;b>>=1,a<<=1,a=a>=mod?a-mod:a) {
        if (b&1) {
            ret+=a;
            if (ret>=mod) ret-=mod;
        }
    } 
    return ret; 
}

ll mpow2(ll x, ll y, ll mod) {
    ll ret=1;
    while (y) {
        if (y&1) ret=mul(ret,x,mod);
        y>>=1, x=mul(x,x,mod);
    }
    return ret%mod;
}

//Primality Test bisa pakai millerRabin atau isPrime (Strong Pseudoprime)

bool millerRabin(ll p) {
    if (p<2 || !(p&1)) return 0;
    if (p==2) return 1;
    ll q=p-1, a, t;
    ll k=0, b=0;
    while (!(q&1)) q>>=1, k++;
    FOR(it ,2) {
        a=rand()%(p-4)+2;
        t=mpow2(a,q,p);
        b=(t==1)||(t==p-1);
        for (ll i=1;i<k&&!b;i++) {
            t=mul(t,t,p);
            if (t==p-1) b=1;
        }
        if (b==0) return 0;
    }
    return 1;
}

bool isPrime(ll p) {
	for(ll i : {2LL, 3LL, 5LL, 13LL, 19LL, 73LL, 193LL, 407521LL, 299210837LL}) {
		if(p == i) return 1;
	}
	for(ll i : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
		ll res = mpow2(i%p, p-1LL, p);
		if(res != 1) return 0;
	}
	return 1;
}

ll pollardRho(ll n,ll c) {
    ll x=2, y=2, i=1, k=2, d;
    while (true) {
        x=(mul(x,x,n)+c);
        if (x>=n) x-=n;
        d=__gcd(x-y,n);
        if (d>1) return d;
        if (++i==k) y=x, k<<=1;
    }
    return n;
}

void factorizeSmall(ll n) {
	for(ll i = 0; i < prime.size(); i++) {
		if(n % prime[i] == 0) {
			if(ans[prime[i]] == 0) {
				fact.push_back(prime[i]);
			}
			ans[prime[i]]++;
			while(n % prime[i] == 0) {
				n /= prime[i];
			}
		}
	}
}

void factorizeBig(ll n) {
	if (n==1) return;
	if (n<MAXN*MAXN) {
		factorizeSmall(n); return;
	}
	if (millerRabin(n)) {
		if(ans[n] == 0) {
			fact.push_back(n);
		}
		ans[n]++; return;
	}
	ll d=n;
	for (ll i=2;d==n;i++) d=pollardRho(n,i);
	factorizeBig(d); factorizeBig(n/d);
}

int main() {
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	sieve(MAXN);
	cin >> n;
	factorizeBig(n);
	sort(fact.begin(), fact.end());
	for(int i = 0; i < fact.size(); i++) {
		cout << fact[i] << " " << ans[fact[i]] << endl;
	}
	return 0;
}
