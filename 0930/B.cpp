#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1200010;
const int inf = 1e18;
int f[N], g[N];
int p[N], w[N], dis[N], pre[N], ne[N];
vector<pair<int, int>> adj[N];
struct point { int p, w; } pnt[N];
struct dijk { int u, dis; } ;
struct Triple { int l, r, typ; } ;
inline bool operator<(const dijk &l, const dijk &r) { return l.dis > r.dis; }
signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> pnt[i].p >> pnt[i].w;
    pnt[0].p = -inf;
    sort(pnt + 1, pnt + n + 1, [&](auto &l, auto &r) { return l.p < r.p; } );
    for (int i = 1; i <= n + 1; ++i)
        pre[i] = pre[i - 1] + pnt[i - 1].w;
    // cerr << "??? " << pnt[1].p << ' ' << pnt[2].p << ' ' << pnt[3].p << '\n';
    while (q--)
    {
        int k;
        cin >> k;
        // cerr << "k = " << k << '\n';
        for (int i = 0; i < N; ++i)
            adj[i].clear();
        memset(dis, -0x3f, sizeof dis);
        vector<pair<int, int>> seg;
        int j = 1;
        for (int i = 1; i <= n; ++i)
        {
            while (j <= n && pnt[j].p <= pnt[i - 1].p + k)
                ++j;
            // cerr << "ooo " << i << ' ' << j << ' ' << pnt[i - 1].p << ' ' << pnt[i - 1].p + k << '\n';
            ne[i] = j;
        }
        int id = n;
        while (ne[id] > n)
            --id;
        memset(f, 0x3f, sizeof f);
        memset(g, 0x3f, sizeof g);
        f[1] = g[1] = 0;
        int p1 = 1, p2 = 1;
        for (int i = 1; i <= n; ++i)
        {
            while (p1 <= n && pnt[p1].p < pnt[i].p + k)
                ++p1;
            while (p2 <= n && pnt[p2].p <= pnt[i - 1].p + k)
                ++p2;
            g[i] = min(g[i], f[i]);
            for (int k = i; k <= p2; ++k)
            {
                g[k] = min(g[k], f[i] + pre[p2] - pre[k]);
                f[k] = min(f[k], g[i] + pre[p2] * 2 - pre[i] - pre[k]);
            }
            for (int k = i; k <= min(j, id); ++k)
                f[k] = min(f[k], f[i] + max(pre[ne[k]] - pre[j], 0ll) + pre[ne[k]] - pre[k]);
            for (int k = p2; k <= j; ++k)
                g[k] = min(g[k], f[i]), f[k] = min(f[k], g[i] + pre[k] - pre[i]);
            f[i + 1] = min(f[i + 1], f[i] + pnt[i].w);
            g[i + 1] = min(g[i + 1], g[i] + pnt[i].w);
        }
        // cerr << "f: ";
        // for (int i = 1; i <= n + 1; ++i)
        //     cerr << f[i] << ' '; cerr << '\n';
        // cerr << "g: ";
        // for (int i = 1; i <= n + 1; ++i)
        //     cerr << g[i] << ' '; cerr << '\n';
        // cerr << "ne: ";
        // for (int i = 1; i <= n; ++i)
            // cerr << ne[i] << ' '; cerr << '\n';
        cout << min(f[n + 1], g[n + 1]) << '\n';
    }
    return 0;
}