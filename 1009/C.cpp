#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
using namespace std;
const int N = 200010;
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

int f[N], g[N], h[N];
int fac[N], inv[N], ifac[N];
inline int binom(int a, int b)
{
    if (b < 0 || a < b)
        return 0;
    return fac[a] * ifac[b] % mod * ifac[a - b] % mod;
}

signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 0; i < 2; ++i)
        fac[i] = inv[i] = ifac[i] = 1;
    for (int i = 2; i < N; ++i)
    {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    while (T--)
    {
        int n, k, d;
        cin >> n >> k >> d;
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        memset(h, 0, sizeof h);
        if (n == 1)
            cout << "1\n";
        else if (k == n)
        {
            if (d == n)
                cout << "1\n";
            else
                cout << "0\n";
        }
        else
        {
            for (int i = 1; i <= min(k, d); ++i)
                h[i] = power(i, i - 1, mod) * (n - k) % mod;
            f[0] = 1;
            for (int i = 1; i <= k; ++i)
                for (int j = 1; j <= i; ++j)
                {
                    f[i] = (f[i] + f[i - j] * binom(i - 1, j - 1) % mod * h[j] % mod) % mod;
                    g[i] = (g[i] + (binom(i - 1, j - 1) * h[j] % mod) * (f[i - j] + g[i - j])) % mod;
                }
            cout << inversion(power(n, n - 2, mod)) * g[k] % mod * power(n, n - k - 1, mod) % mod * inversion(n - k) % mod << '\n';
        }
    }
    return 0;
}