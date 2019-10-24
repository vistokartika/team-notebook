string divide(string number, long long divisor){
	string ans;
	int idx = 0;
	int tmp = number[idx] - '0';
	int len = number.length();
	while(tmp < divisor){
		tmp *= 10;
		tmp += (number[++idx] - '0');
	}
	while(len > idx){
		ans += tmp/divisor + '0';
		tmp = (tmp % divisor) * 10 + number[++idx] - '0';
	}
	if(ans.length() == 0)
		return "0";
	return ans;
}
string multiply(string num1, string num2){
	int len1 = num1.length();
	int len2 = num2.length();
	if(len1 == 0 || len2 == 0) return "0";
	vector<int> result(len1+len2, 0);
	int id1 = 0;
	int id2 = 0;
	int carry, n1, n2, sum;
	for(int i = len1-1; i >= 0; i--){
		carry = 0;
		n1 = num1[i] - '0';
		id2 = 0;
		for(int j = len2-1; j >= 0; j--){
			n2 = num2[j] - '0';
			sum = n1*n2 + result[id1 + id2] + carry;
			carry = sum/10;
			result[id1 + id2] = sum % 10;
			id2++;
		}
		if(carry > 0) result[id1+id2] += carry;
		id1++;
	}
	int i = result.size() - 1;
	while(i >= 0 && result[i] == 0) i--;
	if(i == -1) return "0";
	string s = "";
	while(i >= 0) s += to_string(result[i--]);
	return s;
}
string sum(string num1, string num2){
	int len1 = num1.length();
	int len2 = num2.length();
	if(len1 > len2) swap(num1, num2);
	len1 = num1.length();
	len2 = num2.length();
	string ans = "";
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	int sum, carry = 0;
	for(int i = 0; i < len1; i++){
		sum = (num1[i]-'0') + (num2[i]-'0') + carry;
		ans+= to_string(sum % 10);
		carry = sum/10;
	}
	for(int i = len1; i < len2; i++){
		sum = (num2[i] - '0') + carry;
		ans += to_string(sum % 10);
		carry = sum/10;
	}
	if(carry){
		ans += to_string(carry);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
string diff(string num1, string num2){
	if(num1 < num2)
		swap(num1, num2);
	string ans = "";
	int len1 = num1.length();
	int len2 = num2.length();
	int diff = len1-len2;
	int sub, carry = 0;
	for(int i = len2-1; i >= 0; i--){
		sub = (num1[i+diff]-'0') - (num2[i]-'0') - carry;
		if(sub < 0){
			sub += 10;
			carry = 1;
		}
		else carry = 0;
		ans += to_string(sub);
	}
	for(int i = len1-len2-1; i >= 0; i--){
		if(num1[i] == '0' && carry){
			ans += '9';
			continue;
		}
		sub = (num1[0] - '0') - carry;
		if(i > 0 || sub > 0) ans += to_string(sub);
		carry = 0;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
long long mod(string num, long long a) {
    long long res = 0; 
    for (int i = 0; i < num.length(); i++){
         res = (res*10 + (long long)num[i] - '0') %a;     
	}
    return res;
} 
int main(){
	string num1 = "104";
	string num2 = "035";
	long long modulo = 3;
	long long divisor = 125;
	cout << divide(num1, divisor) << endl;
	cout << multiply(num1, num2) << endl;
	cout << sum(num1, num2) << endl;
	cout << diff(num1, num2) << endl;
	cout << mod(num1,modulo) << endl;
	return 0;
}
