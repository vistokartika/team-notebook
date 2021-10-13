ll mul(ll a, ll b, ll mod) {
	ll ret=0; for (a%=mod,b%=mod;b!=0;b&gt;&gt;=1,a&lt;&lt;=1,a=a&gt;=mod?a-mod:a)
	if (b&amp;1) {ret+=a;if (ret&gt;=mod) ret-=mod;}return ret;}
ll mpow2(ll x, ll y, ll mod) {
	ll ret=1; while (y) {if (y&amp;1) ret=mul(ret,x,mod);y&gt;&gt;=1, x=mul(x,x,mod);}
	return ret%mod;}
bool millerRabin(ll p) {
	if (p==2) return 1; if (p&lt;2||!(p&amp;1)) return 0;
	ll q=p-1,a,t; int k=0, b=0;
	while (!(q&amp;1)) q&gt;&gt;=1, k++;
	FOR(it,2) { a=rand()%(p-4)+2; t=mpow2(a,q,p); b=(t==1)||(t==p-1);
	for (int i=1;i&lt;k&amp;&amp;!b;i++) {t=mul(t,t,p); if (t==p-1) b=1;}
	if (b==0) return 0;} return 1;}
ll pollardRho(ll n,ll c) {
	ll x=2, y=2, i=1, k=2, d;
	while (true) { x=(mul(x,x,n)+c); if (x&gt;=n) x-=n; d=__gcd(x-y,n);
	if (d&gt;1) return d; if (++i==k) y=x, k&lt;&lt;=1;} return n;}
void factorizeBig(ll n) {
	if (n==1) return;
	if (n&lt;MAXN*MAXN) {factorizeSmall(n); return;}
	if (millerRabin(n)) {ans[n]++; return;}
	ll d=n; for (int i=2;d==n;i++) d=pollardRho(n,i);
	factorizeBig(d); factorizeBig(n/d);}
