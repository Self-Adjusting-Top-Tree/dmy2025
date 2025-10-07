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

int a[N];
int f[N][3][2][2];
// f[i][j][0/1][0/1]: 当前考虑到了前 i 个数，当前 (正 + 2负) % 3 的值，当前是 正 还是 负，当前是否存在一堆相邻且符号相同的数  的方案数
// key：合法情况下 (正 + 2负) % 3 = 1

inline void chkmax(int &x, int y)
{
    if (x < y)
        x = y;
}

signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    if (n == 1)
    {
        cout << a[1] << '\n';
        return 0;
    }
    memset(f, -0x3f, sizeof f);
    f[1][1][1][0] = a[1], f[1][2][0][0] = -a[1];
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 2; ++k)
                for (int p = 0; p < 2; ++p)
                {
                    chkmax(f[i + 1][(j + 2) % 3][0][p || !k], f[i][j][k][p] - a[i + 1]);
                    chkmax(f[i + 1][(j + 1) % 3][1][p || k], f[i][j][k][p] + a[i + 1]);
                }
    cout << max(f[n][1][0][1], f[n][1][1][1]) << '\n';
    return 0;
}