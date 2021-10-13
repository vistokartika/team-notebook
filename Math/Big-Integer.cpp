//Big integer operation using string

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
	if(len1 == 0 || len2 == 0){
		return "0";
	}
	
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
		
		if(carry > 0){
			result[id1+id2] += carry;
		}
		
		id1++;
	}
	
	int i = result.size() - 1;
	while(i >= 0 && result[i] == 0){
		i--;
	}
	
	if(i == -1)
		return "0";
		
	string s = "";
	
	while(i >= 0){
		s += to_string(result[i--]);
	}
	
	return s;
}

string sum(string num1, string num2){
	int len1 = num1.length();
	int len2 = num2.length();
	
	if(len1 > len2){
		swap(num1, num2);
	}
	
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

bool isSmaller(string str1, string str2) 
{ 
    if(str1 == str2)
	return true;
    int n1 = str1.length(), n2 = str2.length(); 
  
    if (n1 < n2) 
    	return true; 
    if (n2 < n1) 
    	return false; 
  
    for (int i=0; i<n1; i++){
	if (str1[i] < str2[i]) 
        	return true; 
    	else if (str1[i] > str2[i]) 
       		return false;    
    }
	
    return false; 
} 

string diff(string str1, string str2) 
{ 
    string str = ""; 
    int n1 = str1.length(), n2 = str2.length(); 
  
    reverse(str1.begin(), str1.end()); 
    reverse(str2.begin(), str2.end()); 
      
    int carry = 0; 
  
    for (int i=0; i<n2; i++) 
    { 
        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry); 
        if (sub < 0) 
        { 
            sub = sub + 10; 
            carry = 1; 
        } 
        else
            carry = 0; 
  
        str.push_back(sub + '0'); 
    } 
  
    for (int i=n2; i<n1; i++) 
    { 
        int sub = ((str1[i]-'0') - carry); 
          
        if (sub < 0) 
        { 
            sub = sub + 10; 
            carry = 1; 
        } 
        else
            carry = 0; 
              
        str.push_back(sub + '0'); 
    } 
  
    reverse(str.begin(), str.end()); 
  
    return str; 
} 

void solve(string num1, string num2, int divisor){
	string div = divide(num1, divisor);
	string mult = multiply(num1, num2);
	string add = sum(num1, num2);
	string difference = diff(num1, num2);
}
