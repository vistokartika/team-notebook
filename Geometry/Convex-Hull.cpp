

long long CrossProduct(pair<long long,long long> a, pair<long long,long long> b, pair<long long, long long> c){
	return (b.first - a.first) * (c.se - a.se) - (b.se - a.se) * (c.first - a.first);
}

//collinear ilang

vector<pair<long long,long long> > ConvexHull(vector<pair<long long,long long> > v){
	int sz = 0, n = v.size();
	
	if(n <= 3)
		return v;
	
	vector<pair<long long,long long> >ret(2 * n);
	sort(v.begin(), v.end());

	for(int i = 0 ; i < n ; i++){
		while(sz >= 2 && CrossProduct(ret[sz - 2], ret[sz - 1], v[i]) <= 0){
			sz--;
		}
		ret[sz++] = v[i];
	}
	
	for(int temp = sz + 1, i = n - 2 ; i >= 0 ; i--){
		while(sz >= temp && CrossProduct(ret[sz - 2], ret[sz - 1], v[i]) <= 0){
			sz--;
		}
		ret[sz++] = v[i];
	}
	
	
	ret.resize(sz - 1);
	return ret;
}
