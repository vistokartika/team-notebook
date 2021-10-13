vector<int> z;
string s;

void z_algo(vector<int> &z, string &s){
	int n = s.length(), l = 0, r = 0;
	z = vector<int>(n, 0);
	for(int i = 1 ; i < n ; ++i){
		if(i <= r)
			z[i] = min(z[i - l], r - i + 1);
		
		while(i + z[i] < n && s[i + z[i]] == s[z[i]])
			++z[i];
		
		if(i + z[i] - 1 > r){
			l = i;
			r = i + z[i] - 1;
		}
	}
}
