#include <iostream>
using namespace std;

int i,j,lps[100005];
string a,b;

int main(){
	
	cin>>a>>b;
	int len = 0;
	i = 1;
	lps[0] = 0;
	int lena = a.length();
	int lenb = b.length();
	
	while(i < lenb){
		if(b[i] == b[len]){
			len++;
			lps[i] = len;
			i++;
		}
		else{
			if(len != 0){
				len = lps[len-1];
			}
			else{
				lps[i] = 0;
				i++;
			}
		}
	}
	
	i = j = 0;
	
	while(i < lena){
		if(a[i] == b[j]){
			i++;
			j++;
		}
		if(j == lenb){
			cout<<"possible"<<endl;
			return 0;
		}
		else if(i < lena && b[j] != a[i]){
			if(j != 0){
				j = lps[j-1];
			}
			else{
				i++;
			}
		}
	}
	cout<<"impossible"<<endl;
	return 0;
}

