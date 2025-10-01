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
int a[N];
signed main()
{
    // freopen("string.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int T;
    cin >> T;
    while (T--)
    {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        int mx = -inf * 3, lg2 = 1;
        while (lg2 <= n)
            lg2 = lg2 << 1 | 1;
        ++lg2;
        for (int i = 1; i <= n; ++i)
            for (int j = n; j > i; --j)
                if (n * (n - 1) - i * j <= lg2 * k)
                    mx = max(mx, i * j - k * (a[i] | a[j]));
                else
                    break;
        cout << mx << '\n';
    }
    return 0;
}