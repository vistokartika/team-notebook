typedef vector<int> VI;
typedef pair<int, int> PII;
// returns g = gcd(a, b); finds x, y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
	int xx = y = 0;
	int yy = x = 1;
	while (b) {
		int q = a / b;
		int t = b; b = a%b; a = t;
		t = xx; xx = x - q*xx; x = t;
		t = yy; yy = y - q*yy; y = t;
	}
	return a;
}
// finds all solutions to ax = b (mod n)
VI modular_linear_equation_solver(int a, int b, int n) {
	int x, y; VI ret; int g = extended_euclid(a, n, x, y);
	if (!(b%g)) {
		x = mod(x*(b / g), n);
		for (int i = 0; i < g; i++)
		ret.push_back(mod(x + i*(n / g), n));
	}
	return ret;
}
// Chinese remainder theorem (special case): find z such that
// z % m1 = r1, z % m2 = r2.  Here, z is unique modulo M = lcm(m1, m2).
// Return (z, M).  On failure, M = -1.
PII chinese_remainder_theorem(int m1, int r1, int m2, int r2) {
	int s, t; int g = extended_euclid(m1, m2, s, t);
	if (r1%g != r2%g) return make_pair(0, -1);
	return make_pair(mod(s*r2*m1 + t*r1*m2, m1*m2) / g, m1*m2 / g);
}
// Chinese remainder theorem: find z such that
// z % m[i] = r[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (m[i]).  Return (z, M). On 
// failure, M = -1. Note that we do not require the a[i]'s
// to be relatively prime.
PII chinese_remainder_theorem(const VI &m, const VI &r) {
	PII ret = make_pair(r[0], m[0]);
	for (int i = 1; i < m.size(); i++) {
		ret = chinese_remainder_theorem(ret.second, ret.first, m[i], r[i]);
		if (ret.second == -1) break;
	}
	return ret;
}
// computes x and y such that ax + by = c
// returns whether the solution exists
bool linear_diophantine(int a, int b, int c, int &x, int &y) {
	if (!a && !b){
		if (c) return false;
		x = y = 0;
		return true;
	}
	if (!a){
		if (c % b) return false;
		x = 0; y = c / b; return true;
	}
	if (!b){
		if (c % a) return false;
		x = c / a; y = 0;
		return true;
	}
	int g = gcd(a, b);
	if (c % g) return false;
	x = c / g * mod_inverse(a / g, b / g);
	y = (c - a*x) / b;
	return true;
}
// Returns nCr % p. In this Lucas Theorem based program, 
// this function is only called for n < p and r < p. 
int nCrModpDP(int n, int r, int p) { 
    int C[r+1];  memset(C, 0, sizeof(C)); 
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = min(i, r); j > 0; j--) 
            C[j] = (C[j] + C[j-1])%p; 
    } 
    return C[r]; 
} 
// Lucas Theorem based function that returns nCr % p 
// This function works like decimal to binary conversion 
// recursive function. First we compute last digits of 
// n and r in base p, then recur for remaining digits 
int nCrModpLucas(int n, int r, int p) { 
   if (r==0) 
      return 1; 
   int ni = n%p, ri = r%p; 
   return (nCrModpLucas(n/p, r/p, p) * nCrModpDP(ni, ri, p)) % p;
} 
// Euler's Totient Function using Sieve of Eratosthenes
ll phi(ll n) { 
    ll res = n; 
    // this loop runs sqrt(n / ln(n)) times 
    for (ll i=0; p[i]*p[i] <= n; i++) { 
        if (n % p[i]== 0) { 
            // subtract multiples of p[i] from r 
            res -= (res / p[i]); 
            // Remove all occurrences of p[i] in n 
            while (n % p[i]== 0)  n /= p[i]; 
        } 
    } 
    // when n has prime factor greater than sqrt(n) 
    if (n > 1) res -= (res / n); 
    return res; 
} 
int FLT {
	return pow(a, totient(n)) equivalent 1 (mod n);
}

int main() {
	// expected: 2 -2 1
	int x, y; int g = extended_euclid(14, 30, x, y);
	cout << g << " " << x << " " << y << endl;	
	// expected: 95 451
	VI sols = modular_linear_equation_solver(14, 30, 100);
	for (int i = 0; i < sols.size(); i++) cout << sols[i] << " ";
	cout << endl;
	// expected: 23 105 11 12
	PII ret = chinese_remainder_theorem(VI({ 3, 5, 7 }), VI({ 2, 3, 2 }));
	cout << ret.first << " " << ret.second << endl;
	ret = chinese_remainder_theorem(VI({ 4, 6 }), VI({ 3, 5 }));
	cout << ret.first << " " << ret.second << endl;
	// expected: 5 -15
	if (!linear_diophantine(7, 2, 5, x, y)) cout << "ERROR" << endl;
	cout << x << " " << y << endl;
	// expected: 6
	cout << nCrModpLucas(10, 2, 13) << endl;
	return 0;
}

Catalan Number
f(n)=C(2n,n)/(n+1)|f(n+1)=sum(i=0..n)f(i)*f(n-i)
1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440,
9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420, 24466267020,
91482563640, 343059613650, 1289904147324, 4861946401452