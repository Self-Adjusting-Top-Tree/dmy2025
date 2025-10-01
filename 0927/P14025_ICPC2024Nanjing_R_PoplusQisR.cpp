#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#define int long long
    #define dasongsong cin
    #define ruahao cout
    #define song18 cerr
using namespace std;
const int N = 1000010;
int a[N], p[N], q[N], vis[N];
inline void solve_d(int now, int k, int *p, int *q)
{
    if (!now)
    {
        p[0] = q[0] = 0;
        return;
    }
    if (now == 1)
    {
        p[0] = q[1] = 0;
        p[1] = q[0] = 1;
        return;
    }
    if (k < (1 << (now - 1)))
        solve_d(now - 1, k, p, p + (1 << (now - 1)));
    else
        solve_d(now - 1, k - (1 << (now - 1)), p + (1 << (now - 1)), p);
    for (int i = 0; i < (1 << now); ++i)
        q[i] = p[(1 << now) - i - 1];
    for (int i = 1 << (now - 1); i < (1 << now); ++i)
        p[i] += 1 << (now - 1);
    for (int i = 0; i < (1 << (now - 1)); ++i)
        q[i] += 1 << (now - 1);
}
inline void solve_c(int now, int *p, int *q)
{
    if (!now)
        return;
    if (now <= 2)
    {
        if (now == 1)
        {
            p[0] = q[0] = 0;
            return;
        }
        p[0] = q[1] = 0;
        p[1] = q[0] = 1;
        return;
    }
    int lgx = 1, cnt = 0;
    while ((lgx << 1) <= now)
        ++cnt, lgx <<= 1;
    solve_c(now - lgx, p, p + lgx);
    for (int i = 0; i < now - lgx; ++i)
        p[i] += lgx;
    solve_d(cnt, now - lgx, q + lgx, q);
    for (int i = lgx; i < now; ++i)
        q[i] += lgx;
    for (int i = now; i < lgx * 2; ++i)
        p[i - lgx] = q[i];
}
signed main()
{
    dasongsong.tie(0)->sync_with_stdio(false);
    int T;
    dasongsong >> T;
    while (T--)
    {
        int n;
        dasongsong >> n;
        if (n == 1)
            ruahao << "Yes\n0\n0\n";
        else if (n & 3)
            ruahao << "No\n";
        else
        {
            fill(vis, vis + n + 1, 0);
            solve_c(n >> 2, p, q);
            // song18 << "debug: ";
            // for (int i = 0; i < (n >> 2); ++i)
            //     song18 << p[i] << ' ';
            // song18 << '\n';
            for (int i = 0; i < (n >> 2); ++i)
            {
                a[i << 2] = p[i] << 2;
                a[i << 2 | 1] = p[i] << 2 | 2;
                if (vis[a[i << 2] ^ (i << 2)] || vis[a[i << 2 | 1] ^ (i << 2 | 1)])
                    a[i << 2] ^= 2, a[i << 2 | 1] ^= 2;
                vis[a[i << 2] ^ (i << 2)] = vis[a[i << 2 | 1] ^ (i << 2 | 1)] = 1;
                a[i << 2 | 2] = q[i] << 2 | 3;
                a[i << 2 | 3] = q[i] << 2 | 1;
                if (vis[a[i << 2 | 2] ^ (i << 2 | 2)] || vis[a[i << 2 | 3] ^ (i << 2 | 3)])
                    a[i << 2 | 2] ^= 2, a[i << 2 | 3] ^= 2;
                vis[a[i << 2 | 2] ^ (i << 2 | 2)] = vis[a[i << 2 | 3] ^ (i << 2 | 3)] = 1;
            }
            ruahao << "Yes\n";
            for (int i = 0; i < n; ++i)
                ruahao << i << ' ';
            ruahao << '\n';
            for (int i = 0; i < n; ++i)
                ruahao << a[i] << ' ';
            ruahao << '\n';
        }
    }
}