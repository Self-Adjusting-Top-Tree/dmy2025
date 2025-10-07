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

int a[N], b[N];

signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
            cin >> b[i];
        set<pair<int, int>> odt;
        cout << 0 << ' ';
        odt.emplace(b[1], a[1]);
        map<int, int> yhb;
        yhb[a[1] - b[1]] = 1;
        int all = a[1] - b[1];
        for (int i = 2; i <= n; ++i)
        {
            all += a[i] - b[i];
            auto it = odt.lower_bound({b[i], 0});
            int l = b[i], r = a[i];
            while (it != odt.end() && it->first <= a[i] && it->second >= b[i])
                l = min(l, it->first), r = max(r, it->second), ++it;
            it = odt.lower_bound({b[i], 0});
            if (it != odt.begin())
            {
                it = prev(it);
                int ok = 0;
                while (it->first <= a[i] && it->second >= b[i])
                {
                    l = min(l, it->first), r = max(r, it->second);
                    if (it == odt.begin())
                    {
                        ok = 1;
                        break;
                    }
                    --it;
                }
                if (!ok)
                    ++it;
                while (it != odt.end() && it->first <= a[i] && it->second >= b[i])
                {
                    int _l = it->first, _r = it->second;
                    if (!--yhb[_r - _l])
                        yhb.erase(yhb.find(_r - _l));
                    it = odt.erase(it);
                }
            }
            else
            {
                while (it != odt.end() && it->first <= a[i] && it->second >= b[i])
                {
                    int _l = it->first, _r = it->second;
                    if (!--yhb[_r - _l])
                        yhb.erase(yhb.find(_r - _l));
                    it = odt.erase(it);
                }
            }
            ++yhb[r - l];
            odt.emplace(l, r);
            cout << all - yhb.rbegin()->first << ' ';
        }
        cout << '\n';
    }
    return 0;
}