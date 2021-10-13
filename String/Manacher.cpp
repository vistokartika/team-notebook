//Finding the longest palindromic substring of a string

string manacher(string s){
	int len = s.length();
	if(len == 0){
		return "";
	}
	len = 2*len + 1;
	int lps[len];
	lps[0] = 0;
	lps[1] = 1;
	int c = 1;
	int r = 2;
	int i = 0;
	int imirror;
	int maxlen = 0;
	int maxpos = 0;
	int start, end, diff;
	start = end = diff = -1;

	for(int i = 2; i < len; i++){
		imirror = 2*c-i;
		lps[i] = 0;
		diff = r-i;
		if(diff > 0){
			lps[i] = min(lps[imirror], diff);
		}

		while(((i+lps[i])<len && (i-lps[i])>0) && (((i+lps[i]+1)%2 == 0) || (s[(i+lps[i]+1)/2] == s[(i-lps[i]-1)/2]))){
			lps[i]++;
		}

		if(lps[i] > maxlen){
			maxlen = lps[i];
			maxpos = i;
		}

		if(i + lps[i] > r){
			c = i;
			r = i + lps[i];
		}
	}
	start = (maxpos-maxlen)/2;
	end = start + maxlen - 1;
	string ans = "";
	for(int i = start; i <= end; i++){
		ans += s[i];
	}
	return ans;
} 

void solve(string s){
	string longestpal = manacher(s);
}
