#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
using std::vector;

const int INF = 2100000000;
const int MAXN = 200001;

struct Chamber {
  int x, y, id, diff, sum;
  Chamber(int id) : x(0), y(0), id(id) {}

  void Input() {
    assert(scanf("%d%d", &x, &y) == 2);
    diff = x - y;
    sum = x + y;
  }

  void FilpX() {
    x = -x;
    diff = x - y;
    sum = x + y;
  }

  void SwapXY() {
    std::swap(x, y);
    diff = x - y;
  }
};

struct RawEdge {
  int l, r, d;
  RawEdge(int l, int r, int d) : l(l), r(r), d(d) {}
};

struct TreeEdge {
  int r, d, next;
  TreeEdge() {}
  TreeEdge(int r, int d, int next) : r(r), d(d), next(next) {}
} edge[2 * MAXN];

int n, tot;
int fa[MAXN], x[MAXN], depth[MAXN];
int go[MAXN][18], far[MAXN][18];
vector<Chamber> chambers;
vector<RawEdge> raw_edge;
vector<int> fenwick;

inline int Lowbit(int x) { return x & -x; }

bool CompareChamber(const Chamber &a, const Chamber &b) {
  if (a.x == b.x) return a.y > b.y;
  return a.x > b.x;
}

bool CompareEdge(const RawEdge &a, const RawEdge &b) {
  return a.d < b.d;
}

void Init() {
  tot = 2;
  chambers.clear();
  raw_edge.clear();
  assert(scanf("%d", &n) == 1);
  for (int i = 1; i <= n; ++i) {
    chambers.push_back(Chamber(i));
    chambers.back().Input();
    fa[i] = i;
    x[i] = 0;
  }
}

int GetNearest(int x) {
  int ret = -1;
  for ( ; x; x -= Lowbit(x))
    if (fenwick[x] != -1 && (ret == -1 || chambers[fenwick[x]].sum < chambers[ret].sum))
        ret = fenwick[x];
  return ret;
}

void InsertChamber(int x, int id) {
  for ( ; x < int(fenwick.size()); x += Lowbit(x))
    if (fenwick[x] == -1 || (chambers[id].sum < chambers[fenwick[x]].sum))
      fenwick[x] = id;
}

void AddEdges() {
  vector<int> axis{-INF};
  for (const Chamber &chamber : chambers)
    axis.push_back(chamber.diff);
  std::sort(axis.begin(), axis.end());
  axis.erase(std::unique(axis.begin(), axis.end()), axis.end());
  std::sort(chambers.begin(), chambers.end(), CompareChamber);
  fenwick = vector<int>(axis.size(), -1);
  for (int i = 0; i < n; ++i) {
    const Chamber &chamber = chambers[i];
    int pos = std::lower_bound(axis.begin(), axis.end(), chamber.diff) - axis.begin();
    int nearest = GetNearest(pos);
    if (nearest != -1)
      raw_edge.push_back(RawEdge(chamber.id,
                                 chambers[nearest].id,
                                 chambers[nearest].sum - chamber.sum));
    InsertChamber(pos, i);
  }
}

void AddTreeEdge(int l, int r, int d) {
  edge[tot] = TreeEdge(r, d, x[l]);
  x[l] = tot++;
  edge[tot] = TreeEdge(l, d, x[r]);
  x[r] = tot++;
}

int GetFa(int p) {
  if (fa[p] == p) return p;
  fa[p] = GetFa(fa[p]);
  return fa[p];
}

void Kruskal() {
  if (n == 1) return;
  std::sort(raw_edge.begin(), raw_edge.end(), CompareEdge);
  int left = n - 1;
  for (const RawEdge &e : raw_edge) {
    int fl = GetFa(e.l);
    int fr = GetFa(e.r);
    if (fl != fr) {
      fa[fl] = fr;
      AddTreeEdge(e.l, e.r, e.d);
      if (!(--left)) break;
    }
  }
}

void DFS(int p, int dep, int father) {
  depth[p] = dep;
  for (int i = x[p]; i; i = edge[i].next) {
    if (edge[i].r == father) continue;
    go[edge[i].r][0] = p;
    far[edge[i].r][0] = edge[i].d;
    DFS(edge[i].r, dep + 1, p);
  }
}

void Work() {
  AddEdges();
  for (Chamber &chamber : chambers) chamber.SwapXY();
  AddEdges();
  for (Chamber &chamber : chambers) chamber.FilpX();
  AddEdges();
  for (Chamber &chamber : chambers) chamber.SwapXY();
  AddEdges();
  Kruskal();
  go[1][0] = 0;
  far[1][0] = 0;
  DFS(1, 0, 0);
  for (int j = 1; j < 18; ++j)
    for (int i = 1; i <= n; ++i) {
      go[i][j] = go[go[i][j - 1]][j - 1];
      far[i][j] = std::max(far[i][j - 1], far[go[i][j - 1]][j - 1]);
    }
}

int GetAns(int a, int b) {
  if (depth[a] > depth[b]) std::swap(a, b);
  int ret = 0;
  for (int diff = depth[b] - depth[a], i = 0; diff; ++i, diff >>= 1)
    if (diff & 1) {
      ret = std::max(ret, far[b][i]);
      b = go[b][i];
    }
  if (a == b) return ret;
  for (int j = 17; j >= 0; --j) {
    if (go[a][j] != go[b][j]) {
      ret = std::max(ret, far[a][j]);
      ret = std::max(ret, far[b][j]);
      a = go[a][j];
      b = go[b][j];
    }
  }
  ret = std::max(ret, far[a][0]);
  ret = std::max(ret, far[b][0]);
  return ret;
}

void Answer() {
  int q;
  assert(scanf("%d", &q) == 1);
  while (q--) {
    int st, ed;
    assert(scanf("%d%d", &st, &ed) == 2);
    printf("%d\n", GetAns(st, ed));
  }
}

int main() {
  int cases;
  assert(scanf("%d", &cases) == 1);
  while (cases--) {
    Init();
    Work();
    Answer();
  }
  return 0;
}
