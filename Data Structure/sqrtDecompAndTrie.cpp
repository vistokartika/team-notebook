#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define pb push_back
#define fi first
#define se second
#define UP(a,b,c) for(ll (a)=(b);(a)<(c);(a)++)
#define UU(a,b,c) for(ll (a)=(b);(a)<=(c);(a)++)
#define DN(a,b,c) for(ll (a)=(b);(a)>(c);(a)--)
#define DU(a,b,c) for(ll (a)=(b);(a)>=(c);(a)--)

#define MAX 17

int n, q, a[250005], sq;

struct Node {
	int nxt[2];
	int cnt = 0;

	Node()
	{
		nxt[0] = nxt[1] = -1;
	};
};

struct Block {
	int X = 0;
	vector<Node> trie;

	void insert(int idx, int now, int val)
	{
		if(now == 0)
		{
			trie[idx].cnt++;
			return ;
		}
		bool on = (val & (1LL << (now - 1)));
		if(trie[idx].nxt[on] == -1)
		{
			trie[idx].nxt[on] = trie.size();
			trie.pb(Node());
		}
		insert(trie[idx].nxt[on], now - 1, val);
		trie[idx].cnt++;
	}

	void remove(int idx, int now, int val)
	{
		if(now == 0)
		{
			trie[idx].cnt--;
			return ;
		}
		bool on = (val & (1LL << (now - 1)));
		remove(trie[idx].nxt[on], now - 1, val);
		trie[idx].cnt--;
	}

	pii getVal(int idx, int now)
	{
		if(now == 0)
		{
			return {0, trie[idx].cnt};
		}
		bool on = (X & (1LL << (now - 1)));
		pii ret;
		if(trie[idx].nxt[on] != -1 && trie[trie[idx].nxt[on]].cnt)
		{
			ret = getVal(trie[idx].nxt[on], now - 1);
			ret.fi |= (on ? (1LL << (now- 1)) : 0);
			return ret;
		}
		ret = getVal(trie[idx].nxt[(on ^ 1)], now - 1);
		ret.fi |= (on ? 0 : (1LL << (now - 1)));
		return ret;
	}

	Block()
	{
		X = 0;
		trie.pb(Node());
	}
};
vector<Block> v;

void reset()
{
}

void input()
{
	scanf("%d", &n);
	scanf("%d", &q);
	UP(i, 0, n) scanf("%d", &a[i]);
	sq = sqrt(n);
}

pii getVal(int l, int r)
{
	pii ret = {INT_MAX, 0}, temp;

	while(l <= r)
	{
		if(l % sq == 0 && l + sq - 1 <= r)
		{
			temp = v[l / sq].getVal(0, MAX);
			temp.fi ^= v[l / sq].X;
			l += sq;
		}
		else
		{
			temp = {(a[l] ^ v[l / sq].X), 1};
			l++;
		}
		

		if(ret.fi > temp.fi) ret = temp;
		else if(ret.fi == temp.fi) ret.se += temp.se;
	}

	return ret;
}

void update(int l, int r, int x)
{
	while(l <= r)
	{
		if(l % sq == 0 && l + sq - 1 <= r)
		{
			v[l / sq].X ^= x;
			l += sq;
		}
		else
		{
			v[l / sq].remove(0, MAX, a[l]);
			a[l] ^= x;
			v[l / sq].insert(0, MAX, a[l]);
			l++;
		}
	}
}

void solve()
{
	int l, r, x, type;
	while(q--)
	{
		scanf("%d", &type);
		scanf("%d", &l);
		scanf("%d", &r);
		l--;
		r--;

		if(type == 1)
		{
			pii res = getVal(l, r);
			printf("%d %d\n", res.fi, res.se);
		}
		else
		{
			scanf("%d", &x);
			update(l, r, x);
		}
	}
}

void LetsRock()
{
	v.pb(Block());
	UP(i, 0, n)
	{
		if(i / sq == v.size()) v.pb(Block());
		v[i / sq].insert(0, MAX, a[i]);
	}
	solve();
}

int main()
{
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

		input();
		reset();
		LetsRock();

	return 0;
}

