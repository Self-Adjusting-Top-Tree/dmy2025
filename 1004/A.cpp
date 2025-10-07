#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010;
const int inf = 1e18;
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

char s[N];
int pre[N];

signed main()
{
    // cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i)
        pre[i] = pre[i - 1] + (s[i] == 'S');
    for (int k = 1; k <= n; ++k)
    {
        int cnt = 0;
        for (int i = k; i <= n; )
        {
            ++cnt;
            if (pre[i] == k)
                break;
            assert(pre[i] < k);
            i += k - pre[i];
        }
        cout << cnt << ' ';
    }
    cout << '\n';
    return 0;
}