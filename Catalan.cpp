#include <iostream>
using namespace std;

long long cat(long long n){
	long long ret = 1;
	for(long long i = 0; i < n; i++){
		ret = ret*(2*n-i);
		ret = ret/(i+1);
	}
	ret = ret/(n+1);
	return ret;
}

int main(){
	long long n;
	cin>>n;
	cout<<cat(n)<<endl;
}
