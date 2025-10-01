#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define int long long
using namespace std;
const int N = 4010;
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
int c[N], t[N], cst[N];
int fac[N], inv[N], ifac[N];
int f[4010][4010], g[2][4010];
vector<int> scc[N];
inline int binom(int a, int b)
{
    if (b < 0 || a < b)
        return 0;
    return fac[a] * ifac[b] % mod * ifac[a - b] % mod;
}
signed main()
{
    // freopen("a.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    for (int i = 0; i < 2; ++i)
        fac[i] = inv[i] = ifac[i] = 1;
    for (int i = 2; i < N; ++i)
    {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    for (int i = 1; i <= n; ++i)
        cin >> t[i], scc[t[i]].emplace_back(i), cst[t[i]] += c[i];
    f[0][0] = 1;
    int fx = 1;
    for (int i = 1; i <= n; ++i)
        fx = fx * ifac[c[i]] % mod;
    int all = 0;
    for (int i = 1; i <= n; ++i)
    {
        int o = min(cst[i], (int)scc[i].size());
        all += o;
        for (int j = 0; j <= all; ++j)
            for (int k = 0; k <= min(j, o); ++k)
                f[i][j] = (f[i][j] + f[i - 1][j - k] * binom(scc[i].size(), k) % mod * binom(cst[i], k) % mod * fac[k] % mod) % mod;
    }
    // int all = 0;
    // for (int i = 1; i <= n; ++i)
    // {
    //     memset(g, 0, sizeof g);
    //     g[1][0] = 1;
        
    // }
    // cerr << "wa: ";
    // for (int i = 0; i <= n; ++i)
    //     cout << f[n][i]*fac[n-i]%mod << ' ';
    // cout << '\n';
    int cnt = 0;
    for (int i = 0; i <= all; ++i)
        if (i & 1)
            cnt = (cnt + mod - f[n][i] * fac[n - i] % mod) % mod;
        else
            cnt = (cnt + f[n][i] * fac[n - i] % mod) % mod;
    // cerr<<"fx="<<fx<<'\n';
    cout << cnt * fx % mod << '\n';
    return 0;
}

// 下次遇见计数 记得先考虑二项式反演