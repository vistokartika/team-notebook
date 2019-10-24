str pattern,text;
int lps[200],kmp[200];
//longest proper prefix which is also suffix
void build_lps (){
    int j = 0; lps[0]=0;
    int i = 1;
    while(i<pattern.size()){
        if(pattern[i]==pattern[j]){
            j++; lps[i]=j;i++;
        }
        else{
            if(j>0) j = lps[j-1];
            else{
                lps[i]=0;
                i++;
            }
        }
    }
}
void kmp_search(){
    int j = 0; int i = 0;
    build_lps();
    while(i<text.size()){
        if(text[i]==pattern[j]){
            j++; kmp[i] = j; i++;
            if(j==pattern.size()) j=lps[j-1];
        }
        else{
            if(j!=0) j = lps[j-1];
            else{
                kmp[i]=0; i++;
            }
        }
    }
}
int main(){
    cin>>text>>pattern;
    kmp_search();
    for(int i=0;i<text.size();i++)cout<<kmp[i]<<" ";
}
