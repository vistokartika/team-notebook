#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef string str;
str text,pattern;
int z[200];
void z_algo (){
    str s = pattern + "$" + text;
    int l=0,r=0;
    for(int i=1;i<s.size();i++){
        if(i>r){
            // index > z-box : find new [l,r] interval
            bool found=false;
            for(int j=i;j<s.size();j++){
                if(s[j]==s[j-i]){
                    if(!found){found=true; l=i;}
                    r=j;
                }
                else{break;}
            }
            if(found){z[i]=r-l+1;}
            else{z[i]=0;}
        }
        else{
            int k = i-l;
            // z[k] >= remaining space in z-box : find new [l,r] interval
            if(z[k] >= r-i+1){
                l = i;
                for(int j=i;j<s.size();j++){
                    if(s[j]==s[j-i]){r=j;}
                    else{break;}
                }
                z[i]=r-l+1;
            }
            // z[k] < remaining space in z-box : z[i] = z[k]
            else{
                z[i]=z[k];
            }
        }
    }
}
int main(){
    // finding pattern in a text O (N)
    cin>>text;
    cin>>pattern;
    z_algo();
    for(int i=0;i<text.size()+pattern.size()+1;i++)cout<<z[i]<<" ";
}
