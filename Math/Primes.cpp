//Generating prime numbers from 1 to n, counting numbers from 1..n coprime to n, finding the sum of the divisors of n

const int MSIZE = 1000000;
int lpf[MSIZE+10]
vector<long long> primes;

void sieve(int n){
	for(int i = 0; i <= n; i++)
		lpf[i] = 0;
	
	for(long long i = 2; i <= n; i++){
		if(lpf[i] == 0){
			lpf[i] = i;
			primes.push_back(i);
		}
		for(int j = 0; j < primes.size() && primes[j]*i <= n; j++){
			lpf[primes[j]*i] = primes[j];
		}
	}
}

long long eulerphi(long long n){
	double ans = n;
	long long prime, idx = 0;
	while(primes[idx] * primes[idx] <= n){
		prime = primes[idx];
		if(n % prime == 0){
			while(n % prime == 0){
				n /= prime;
			}
			ans *= (1.0 - (1.0/double(prime)));
		}
		idx++;
	}
	if(n > 1){
		ans *= (1.0 - (1.0/(double)n));
	}
	return (long long)ans;
}

long long sumdiv(long long n){
	long long ans = 1;
	long long prime, idx = 0;
	while(primes[idx] * primes[idx] <= n){
		long long power = 0;
		prime = primes[idx];
		while(n % prime == 0){
			n /= prime;
			power++;
		}
		ans *= ((long long)pow((double)prime, power+1.0)-1) / (prime-1);
		idx++;
	}
	if(n != 1){
		ans *= ((long long)pow((double)n, 2.0)) / (n-1);
	}
	return ans;
}

void solve(int n){
	sieve(n);

	//count of numbers from 1..n coprime to n
	long long totatives = eulerphi(n);
	
	//sum of divisors of n
	long long sum = sumdiv(n);
}
