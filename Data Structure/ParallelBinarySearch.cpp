#include <bits/stdc++.h>
using namespace std;
 
const int N = 100005;
 
vector<int> proc[N];
int lo[N], hi[N], pos[N];
int pset[N];
int n,m,ask;
 
int tipe[N], a[N], b[N];
 
// inisialisasi disjoint set
void reset() {
  for(int i = 1 ; i <= n ; i++)
    pset[i] = i;
}
 
// cari root disjoint set
int finds(int x) {
  return x == pset[x] ? x : pset[x] = finds(pset[x]);
}
 
// menggabungkan disjoint set
void join(int u,int v) {
  u = finds(u); v = finds(v);
  pset[u] = v;
}
 
// baca input
void read() {
  scanf("%d %d",&n,&m);
  for(int i = 1 ; i <= m ; i++)
    scanf("%d %d %d",tipe + i,a + i,b + i);
}
 
// jawab-jawabin query
void solve() {
  ask = 0;
  // inisialisasi low dan high
  for(int i = 1 ; i <= m ; i++)
    if(tipe[i] == 2) {
      lo[ask] = 1;
      hi[ask] = i + 1;
      pos[ask] = i;
 
      proc[(i + 2) / 2].push_back(ask);
      ask++;
    }
 
  bool change = 1;
  // O(log M)
  while(change) {
    change = 0;
    reset();
 
    // O(M)
    for(int i = 1 ; i <= m ; i++) {
      // O(1)
      if(tipe[i] == 1) join(a[i],b[i]);
 
      // proses semua query yang mid-nya sekarang di i
      while(!proc[i].empty()) {
        int posisi = proc[i].back();
        int idx = pos[posisi];
        proc[i].pop_back();
 
        int u = a[idx];
        int v = b[idx];
 
        // O(1)
        if(finds(u) == finds(v)) {
          hi[posisi] = i;
        }
        else {
          lo[posisi] = i+1;
        }
 
        // masih ada yang belum selesai
        if(lo[posisi] < hi[posisi]) {
          proc[(lo[posisi] + hi[posisi]) / 2].push_back(posisi);
          change = 1;
        }
      }
    }
  }
 
  // output semua jawaban
  for(int i = 0 ; i < ask ; i++) {
    int ret = -1;
    if(lo[i] <= pos[i]) ret = lo[i];
    printf("%d\n",ret);
  } 
}
 
int main() {
  int t; scanf("%d",&t);
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    solve();
  }
  return 0;
}