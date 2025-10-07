#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010;
const int inf = 1e18;
const int mod = 1e9 + 7;

inline int power(int a, int b, int c)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % c;
        a = a * a % c, b >>= 1;
    }
    return ans;
}

inline int inversion(int x) { return power(x, mod - 2, mod); }

struct BIT
{
    int tree[N];
    inline BIT() { memset(tree, 0, sizeof tree); }
    inline void clr(int x) { for (; x < N; x += (x &- x)) tree[x] = 0; }
    inline void add(int x, int v) { for (; x < N; x += (x &- x)) tree[x] += v; }
    inline int qry(int x) { int s = 0; for (; x; x -= (x &- x)) s += tree[x]; return s; }
    inline int qry(int l, int r) { return qry(r) - qry(l - 1); }
};

int a[N], b[N], c[N], res[N];
namespace sub1
{
    BIT fwt;
    inline void solve([[maybe_unused]]int n)
    {
        for_each(a + 1, a + n + 1, [&](auto &o) { cin >> o; });
        for (int i = 1; i <= n; ++i)
            b[i] = a[i] - i, c[i] = b[i];
        sort(c + 1, c + n + 1);
        int _ = unique(c + 1, c + n + 1) - c - 1;
        for (int i = 1; i <= n; ++i)
            b[i] = lower_bound(c + 1, c + _ + 1, b[i]) - c;
        for (int i = 1; i <= n; ++i)
        {
            fwt.add(b[i], 1);
            res[i] = fwt.qry(b[i] - 1);
        }
        for (int i = 1; i <= n; ++i)
            fwt.clr(b[i]);
        for (int i = 1; i <= n; ++i)
            b[i] = a[i] + i, c[i] = b[i];
        sort(c + 1, c + n + 1);
        _ = unique(c + 1, c + n + 1) - c - 1;
        for (int i = 1; i <= n; ++i)
            b[i] = lower_bound(c + 1, c + _ + 1, b[i]) - c;
        for (int i = n; i; --i)
        {
            fwt.add(b[i], 1);
            res[i] += fwt.qry(b[i] - 1);
        }
        for_each(res + 1, res + n + 1, [&](auto &o) { cout << o + 1 << '\n'; });
    }
}
namespace sub2
{
    int qidx, res[N];
    struct qwq { int l, r, val, id; } q[N << 2];
    BIT fwt;
    inline void solve1()
    {
        // cerr << "uuu\n";
        for (int i = 0; i < N; ++i)
            fwt.tree[i] = 0;
        // cerr << "vvv\n";
        sort(q + 1, q + qidx + 1, [&](auto &l, auto &r) { return l.val < r.val || l.val == r.val && l.id < r.id; });
        // cerr << "www\n";
        for (int i = 1; i <= qidx; ++i)
        {
            // cerr << "solve when i=" << i << '\n';
            if (q[i].id)
                res[q[i].id] += fwt.qry(q[i].l, q[i].r);
            else
                fwt.add(q[i].l, 1);
        }
    }
    inline void solve2()
    {
        for (int i = 0; i < N; ++i)
            fwt.tree[i] = 0;
        sort(q + 1, q + qidx + 1, [&](auto &l, auto &r) { return l.val < r.val || l.val == r.val && l.id < r.id; });
        for (int i = 1, j = 1; i <= qidx; i = j + 1, ++j)
        {
            while (j < qidx && q[i].val == q[j + 1].val)
                ++j;
            for (int k = i; k <= j; ++k)
                res[q[k].id] = max(res[q[k].id], i - 1);
        }
    }
    inline void solve([[maybe_unused]]int n)
    {
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
        {
            int len = min(i - 1, n - i);
            q[++qidx] = {1, i - len - 1, a[i] + n - i - 1, i};
            q[++qidx] = {i + len + 1, n, a[i] + i - 2, i};
            q[++qidx] = {i, i, a[i], 0};
        }
        // cerr << "!\n";
        solve1();
        qidx = 0;
        for (int i = 1; i <= n; ++i)
        {
            int len = min(i - 1, n - i);
            q[++qidx] = {i - len, i - 1, a[i] + i - 1, i};
            q[++qidx] = {i, i, a[i] + i, 0};
        }
        solve1();
        qidx = 0;
        for (int i = 1; i <= n; ++i)
        {
            int len = min(i - 1, n - i);
            q[++qidx] = {i + 1, i + len, a[i] - i - 1, i};
            q[++qidx] = {i, i, a[i] - i, 0};
        }
        solve1();
        qidx = 0;
        for (int i = 1; i <= n; ++i)
            q[++qidx] = {0, 0, a[i] - i, i};
        solve2();
        qidx = 0;
        for (int i = 1; i <= n; ++i)
            q[++qidx] = {0, 0, a[i] + i, i};
        solve2();
        for (int i = 1; i <= n; ++i)
            cout << res[i] + 1 << '\n';
    }
}

signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int n, p;
    cin >> n >> p;
    ((p == 1) ? sub1::solve : sub2::solve)(n);
}