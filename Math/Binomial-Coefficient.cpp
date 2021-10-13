//Finding the value of nCr and nth catalan number

int binomial(int n, int k){
	int res = 1;
	if(k > n-k){
		k = n-k;
	}

	for(int i = 0; i < k; i++){
		res *= (n-i);
		res /= (i+1);
	}
	return res;
}

void solve(int n, int k){
	int ans = binomial(n, k);

	//catalan number using nCr
	int catalan = binomial(2*n, n)/(n+1);

}
