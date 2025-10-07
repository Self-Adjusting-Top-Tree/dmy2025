#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010;
const int inf = 2e9;
const int mod = 998244353;

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

int a[N];
vector<int> scc[64];
inline int highbit(int x)
{
    for (int i = 60; ~i; --i)
        if (x >> i & 1)
            return i;
    return 0;
}

signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n, f[64] = {0};
        cin >> n;
        for (int i = 0; i <= 60; ++i)
            scc[i].clear(), f[i] = 0;
        for (int i = 1; i <= n; ++i)
            cin >> a[i], scc[highbit(a[i])].emplace_back(a[i]);
        for (int i = 0; i <= 60; ++i)
            for (int &j : scc[i])
            {
                int ff = 1;
                for (int k = 0; k < i; ++k)
                    if (j >> k & 1)
                        ff += f[k];
                f[i] = max(f[i], ff);
            }
        cout << accumulate(f, f + 61, 0ll) << '\n';
    }
    return 0;
}
