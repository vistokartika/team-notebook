//Finding the starting index of a substring in a longer string

const int MaxLen = 1000000;
int backtable[MaxLen];

void preprocess(string pattern){
	int patlen = pattern.length();
	int i = 0;
	int j = -1;
	backtable[0] = -1;
	while(i < patlen){
		while(j >= 0 && pattern[i] != pattern[j]){
			j = backtable[j];
		}
		i++;
		j++;
		backtable[i] = j;
	}
}

vector<int> search(string text, string pattern){
	int len = text.length();
	int patlen = pattern.length();
	int i, j;
	i = j = 0;
	vector<int> idx;
	while(i < len){
		while(j >= 0 && text[i] != pattern[j]){
			j = backtable[j];
		}
		i++;
		j++;
		if(j == patlen){
			idx.push_back(i-j);
			j = backtable[j];
		}
	}
	return idx;
}

void solve(string text, string pattern){
	preprocess(pattern);
	vector<int> idx = search(text, pattern);
}
