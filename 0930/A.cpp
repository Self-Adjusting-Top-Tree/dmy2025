#pragma GCC optimize(3, "Ofast", "inline", "unroll-loops")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010;
const int inf = 1e18;
const int mod = 1e9 + 7;
inline int power(int a, int b, int c)
{
    a %= c;
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = 1ll * ans * a % c;
        a = 1ll * a * a % c, b >>= 1;
    }
    return ans;
}
inline int inversion(int x) { return power(x, mod - 2, mod); }

int a[N], vis[N];
vector<int> v[N];

int tree[N], la[N];
inline void add(int x, int v) { for (; x < N; x += (x &- x)) tree[x] += v; }
inline int qry(int x) { int s = 0; for (; x; x -= (x &- x)) s += tree[x]; return s; }

signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n + n; ++i)
        cin >> a[i], v[a[i]].emplace_back(i);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        int a = v[i][0], b = v[i][1];
        cnt += min(b - a - 1, n + n - b + a - 1);
    }
    for (int i = 1; i <= n + n; ++i)
    {
        if (vis[a[i]])
            cnt -= qry(i) - qry(la[a[i]]), add(la[a[i]], -1);
        else
            la[a[i]] = i, vis[a[i]] = 1, add(i, 1);
    }
    cout << cnt << '\n';

    cout << "Augustus" << "\n";
    return 0;
}


