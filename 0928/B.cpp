#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define int long long
using namespace std;
const int N = 1000010;
const int mod = 998244353;
const int inf = 1e18;
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
int d[N], l[N], r[N], pre[N];
signed main()
{
    // freopen("string.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> d[i];
    for (int i = 1; i <= n; ++i)
        cin >> l[i];
    for (int i = 1; i <= n; ++i)
        cin >> r[i];
    int a0, b0;
    cin >> a0 >> b0;
    int m1 = a0;
    for (int i = 1; i <= n; ++i)
        m1 = min(m1 + d[i], l[i]);
    int all = accumulate(d + 1, d + n + 1, 0ll);
    int res1 = m1 + b0 + all;
    m1 = b0;
    for (int i = 1; i <= n; ++i)
        m1 = min(m1 + d[i], r[i]);
    int res2 = m1 + a0 + all;
    int ta0 = a0, tb0 = b0;
    for (int i = 1; i <= n; ++i)
    {
        a0 += d[i], b0 += d[i];
        if (a0 > l[i] && b0 > r[i])
        {
            if (a0 - l[i] > b0 - r[i])
                b0 = r[i];
            else
                a0 = l[i];
        }
    }
    int res3 = a0 + b0;
    a0 = ta0, b0 = tb0;
    for (int i = 1; i <= n; ++i)
        pre[i] = pre[i - 1] + d[i];
    vector<pair<int, int>> v;
    for (int i = 1; i <= n; ++i)
        v.emplace_back(l[i] - pre[i], r[i] - pre[i]);
    vector<int> vv = {a0};
    for (auto &o : v)
        if (o.first <= a0)
            vv.emplace_back(o.first);
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    sort(v.begin(), v.end());
    int pos = 0, res4 = -inf, cur = inf;
    for (int &i : vv)
    {
        while (pos < v.size() && v[pos].first < i)
            cur = min(cur, v[pos++].second);
        res4 = max(res4, min(cur, b0) + i + pre[n] * 2);
    }
    // cerr << "res4 = " << res4 << '\n';
    int res = max({res1, res2, res3, res4});
    srand(time(0));
    a0 = ta0, b0 = tb0;
    for (int $ = 0; $ < 126; ++$)
    {
        int x = a0, y = b0;
        for (int i = 1; i <= n; ++i)
        {
            x += d[i], y += d[i];
            if (x > l[i] && y > r[i])
            {
                if (rand() & 1)
                    y = r[i];
                else
                    x = l[i];
            }
        }
        res = max(res, x + y);
    }
    cout << res << '\n';
    // cout << max({res1, res2, res3, res4}) << '\n';
    return 0;
}


