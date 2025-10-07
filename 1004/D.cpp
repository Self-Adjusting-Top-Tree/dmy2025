// CF1149D

#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 510;
vector<pair<int, int>> adj[N];
int fa[N], mp[N][N], block[N], siz[N];
int rnm[N];
int f[1 << 18][75];
// f[i][j]: 当前走过了 i 集合内的连通块，当前位于 j 点的最短路长度
struct Node {
    int x, y, dis;
    bool operator<(const Node &r) const {
        return dis > r.dis;
    }
};
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
        mp[x][y] = mp[y][x] = w;
    }
    iota(fa + 1, fa + n + 1, 1);
    fill(siz + 1, siz + n + 1, 1);
    for (int i = 1; i <= m; ++i)
        for (auto &[j, w] : adj[i])
            if (a == w && i > j && find(i) != find(j)) siz[find(j)] += siz[find(i)], fa[find(i)] = find(j);
    int index = 0;
    for (int i = 1; i <= n; ++i)
        if (fa[i] == i && siz[i] > 3) block[i] = rnm[i] = ++index;
    int ip = index;
    for (int i = 1; i <= n; ++i)
        if (fa[i] == i && siz[i] <= 3) rnm[i] = ++ip;
    memset(f, 0x3f, sizeof f);
    priority_queue<Node> q;
    int fir = 0;
    if (rnm[find(1)] <= index) fir = 1 << (rnm[find(1)] - 1);
    q.push({fir, 1, f[fir][1] = 0});
    while (q.size()) {
        auto [x, y, Dis] = q.top();
        q.pop();
        if (f[x][y] >= Dis) {
            for (auto &[u, v] : adj[y]) {
                if (v == b) {
                    if (rnm[find(u)] == rnm[find(y)]) continue;
                    if (rnm[find(u)] <= index && (x >> (rnm[find(u)] - 1) & 1)) continue;
                }
                int nm = x;
                if (v == b && rnm[find(u)] <= index) nm |= (1 << (rnm[find(u)] - 1));
                if (f[nm][u] > f[x][y] + v) {
                    f[nm][u] = f[x][y] + v;
                    q.push({nm, u, f[nm][u]});
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        int res = 1e18;
        for (int j = 0; j < (1 << index); ++j)
            res = min(res, f[j][i]);
        cout << res << ' ';
    }
    cout << '\n';
    return 0;
}