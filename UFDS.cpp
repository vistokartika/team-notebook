#include <bits/stdc++.h>

using namespace std;

int findparent(int x) { 
    if (parent[x] == x) 
        return x; 
    return parent[x] = findparent(parent[x]); 
} 

void join(int x, int y)
{
	int tempx = findparent(x);
	int tempy = findparent(y);
	if(tempx != tempy)
		parent[tempx] = tempy;
}

bool check(int x, int y)
{
	int tempx = findparent(x);
	int tempy = findparent(y);
	if(tempx == tempy)
		return 1;
	return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
}


