#include <bits/stdc++.h>
using namespace std;

const int N = (int)2e5;
const int NIL = 0;

class Trie {
    // construct a trie containing all patterns using this Node
    class Node { public: int idx, ptr[52], fail, jump; int val, depth; };
    // aho corasick helper
    int __fail(int idx, int idxChild, int repeat=0) {
        if (repeat == 1) return idx;
        if (dat[idx].ptr[idxChild] != NIL) return dat[idx].ptr[idxChild];
        return __fail(dat[idx].fail, idxChild, idx==dat[idx].fail);
    }
    inline int __suffixLink(int idx) {
        return (dat[idx].idx != 0) ? idx : dat[idx].jump;
    }

    Node dat[2*N+5];
    int cnt;
    int head;

    int new_node(int _depth=0) {
        dat[cnt+1].idx = 0;
        for (int i=0; i<52; i++) {
            dat[cnt+1].ptr[i] = NIL;
        }
        dat[cnt+1].fail = NIL;
        dat[cnt+1].jump = NIL;
        dat[cnt+1].val = 0;
        dat[cnt+1].depth = _depth;
        return cnt += 1;
    }

public:
    int reset() {
        cnt = NIL;
        return head = new_node();
    }

    int insert(char s[]) {
        int curr = head;
        for (int i=0; s[i]; i++) {
            if (dat[curr].ptr[s[i] - 'a'] == NIL) {
                dat[curr].ptr[s[i] - 'a'] = new_node(i+1);
            }
            curr = dat[curr].ptr[s[i] - 'a'];
        }
        dat[curr].idx = 1;
        dat[curr].val += 1;
        return 0;
    }

    // aho corasick, build process by layer
    inline void ahoCorasick() {
        queue<int> bfs;  while (!bfs.empty()) bfs.pop();
        // construct root first
        dat[1].fail = dat[1].jump = head;  bfs.push(head);
        while (!bfs.empty()) {
            int idx = bfs.front(); bfs.pop();
            // construct its children
            for (int i=0; i<52; i++) if (dat[idx].ptr[i] != NIL) {
                int next = dat[idx].ptr[i];
                dat[next].fail = __fail(dat[idx].fail, i, (idx==head));
                dat[next].jump = __suffixLink(dat[next].fail);
                bfs.push(next);
    }   }   }

    long long dp[N+5];

    long long count_first(int idx, int curr) {
        long long res = (long long)0;
        while (curr != head) {
            res += (long long)dat[curr].val;
            curr = dat[curr].jump;
        }
        return res;
    }

    long long count_second(int idx, int curr) {
        long long res = (long long)0;
        while (curr != head) {
            if (idx - dat[curr].depth >= 0) {
                res += (long long)dat[curr].val * dp[idx - dat[curr].depth];
            }
            curr = dat[curr].jump;
        }
        return res;
    }

    long long solve(char s[]) {
        long long res = 0;
        int curr = head;

        for (int i=0; s[i]; i++) {
            while (curr != head && dat[curr].ptr[s[i] - 'a'] == NIL) {
                curr = dat[curr].fail;
            }
            if (dat[curr].ptr[s[i] - 'a'] != NIL) {
                curr = dat[curr].ptr[s[i] - 'a'];
            }

            dp[i] = count_first(i, curr);
            res += count_second(i, curr);
        }
        return res;
    }
};

char s[N+5];
char pat[N+5];
Trie ds;

int main() {
    ds.reset();

    scanf("%s", s);
    int n; scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%s", pat);
        ds.insert(pat);
    }

    ds.ahoCorasick();

    long long res = ds.solve(s);
    printf("%lld\n", res);
    return 0;
}
