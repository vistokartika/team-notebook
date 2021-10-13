struct suffix{
	int at;
	int rank[2];
};

int Compare(suffix a, suffix b){
	return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ? 1: 0) : (a.rank[0] < b.rank[0] ? 1: 0);
}

suffix suf[1000005];
int indexOf[1000005];

void buildSuffixArray(string &txt, int &n, vector<ll> &pos){
	for(int i = 0 ; i < n ; i++){
		suf[i].at = i;
		suf[i].rank[0] = txt[i];
		suf[i].rank[1] = (i == n - 1 ? -1 : txt[i + 1]);
	}

	sort(suf, suf + n, Compare);

	for(int k = 4 ; k < 2 * n ; k *= 2){
		int rank = 0;
		int prev_rank = suf[0].rank[0];
		suf[0].rank[0] = 0;
		indexOf[suf[0].at] = 0;
		
		for(int i = 1 ; i < n ; i++){
			if(prev_rank == suf[i].rank[0] && suf[i].rank[1] == suf[i - 1].rank[1]){
				suf[i].rank[0] = rank;
			}
			else{
				prev_rank = suf[i].rank[0];
				suf[i].rank[0] = ++rank;
			}
			indexOf[suf[i].at] = i;
		}
		
		for(int i = 0 ; i < n ; i++){
			int nextIndex = suf[i].at + k / 2;
			suf[i].rank[1] = (nextIndex >= n ? -1 : suf[indexOf[nextIndex]].rank[0]);
		}
		
		sort(suf, suf + n, Compare);
	}

	for(int i = 0 ; i < n ; i++)
		pos.push_back(suf[i].at);
}

void kasai(string &txt, vector<ll> &suffixArr, vector<ll> &lcp){
	int n = suffixArr.size();
	lcp = vector<ll>(n, 0);
	vector<int> invSuff(n, 0);

	for (int i=0; i < n; i++)
		invSuff[suffixArr[i]] = i;

	int k = 0;
	for (int i = 0; i < n; i++){
		if (invSuff[i] == n-1){
			k = 0;
			continue;
		}

		int j = suffixArr[invSuff[i]+1];

		while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
			k++;

		lcp[invSuff[i]] = k;

		if (k > 0) k--;
	}
}

vector<ll> idx;
vector<ll> lcp;
int n;
string s;
