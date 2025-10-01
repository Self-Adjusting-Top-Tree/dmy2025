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
struct bucket
{
    int a[26];
    inline bucket() { memset(a, 0, sizeof a); }
    inline ~bucket() { memset(a, 0, sizeof a); }
    inline bool operator==(const bucket &r) const 
    {
        for (int i = 0; i < 26; ++i)
            if (a[i] != r.a[i])
                return 0;
        return 1;
    }
};
struct myhash
{
    inline int rnd(int x) const { x ^= x << 13; x ^= x >> 7; return x ^ x << 17; }
    inline int operator()(const bucket &_) const
    {
        static const int f_rand = chrono::steady_clock::now().time_since_epoch().count();
        int x = 0;
        for (int i = 0; i < 26; ++i)
            x = (x * 13ll + _.a[i]) % 998244353;
        return rnd(x + f_rand);
    }
    inline int operator()(const pair<pair<int, int>, pair<int, int>> &_) const
    {
        static const int f_rand = chrono::steady_clock::now().time_since_epoch().count();
        return rnd(_.first.first * 123456789 + _.first.second * 1145141 + _.second.first * 234567 + _.second.second + f_rand);
    }
};

/*

key: 若有解，则答案一定不超过 2
对 n 的值根号分治

*/

__gnu_pbds::gp_hash_table<bucket, int, myhash> id;
__gnu_pbds::gp_hash_table<pair<pair<int, int>, pair<int, int>>, int, myhash> hh[155][155];
string s[N];
int bit[N], bit2[N];
vector<int> h1[N], h2[N], v[N], mx[N];
const int m1 = 1e9 + 9, m2 = 998244853;
const int b1 = 131, b2 = 13331;
inline int loyalty(int id, int l, int r) { if (l > r) return 0; return (h1[id][r] - (l ? h1[id][l - 1] : 0) * bit[r - l + 1] % m1 + m1) % m1; }
inline int luminescent(int id, int l, int r) { if (l > r) return 0; return (h2[id][r] - (l ? h2[id][l - 1] : 0) * bit2[r - l + 1] % m2 + m2) % m2; }
inline int loyalty(int i1, int i2, int l, int r) { return loyalty(i1, l, r) == loyalty(i2, l, r) && luminescent(i1, l, r) == luminescent(i2, l, r); }
signed main()
{
    // freopen("string.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    bit[0] = bit2[0] = 1;
    for (int i = 1; i < N; ++i)
    {
        bit[i] = bit[i - 1] * b1 % m1;
        bit2[i] = bit2[i - 1] * b2 % m2;
    }
    int n, idx = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> s[i];
        bucket buc;
        for (char &j : s[i])
            ++buc.a[j - 'a'];
        if (!id[buc])
            id[buc] = ++idx;
        v[id[buc]].emplace_back(i);
        h1[i].emplace_back(s[i][0]);
        h2[i].emplace_back(s[i][0]);
        for (int j = 1; j < s[i].size(); ++j)
        {
            h1[i].emplace_back((h1[i][j - 1] * b1 + s[i][j]) % m1);
            h2[i].emplace_back((h2[i][j - 1] * b2 + s[i][j]) % m2);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= idx; ++i)
        cnt += v[i].size() * (n - v[i].size());
    cnt *= 500;
    for (int i = 1; i <= n; ++i)
    {
        int l = 0, r = 0;
        while (r < s[i].size() - 1)
        {
            if (s[i][r + 1] < s[i][r])
                while (l <= r)
                {
                    mx[i].emplace_back(r);
                    ++l;
                }
            ++r;
        }
        while (l < s[i].size())
        {
            mx[i].emplace_back(s[i].size() - 1);
            ++l;
        }
    }
    // cerr << "ooo " << v[1][0] << ' ' << v[1][1] << ": " << loyalty(v[1][0], s[1].size() - 1, s[1].size() - 1) << ' ' << loyalty(v[1][1], s[1].size() - 1, s[1].size() - 1) << '\n';
    // cout << "debug " << cnt << '\n';
    // return 0;
    if (n <= 3500)
    {
        // cerr << "idx = " << idx << '\n';
        for (int i = 1; i <= idx; ++i)
            for (int _ = 0; _ < v[i].size(); ++_)
                for (int $ = _ + 1; $ < v[i].size(); ++$)
                {
                    int j = v[i][_], k = v[i][$];
                    int l = 0, r = (int)s[i].size() - 2;
                    while (l <= r)
                    {
                        int mid = l + r >> 1;
                        (loyalty(j, k, 0, mid)) ? (l = mid + 1) : (r = mid - 1);
                    }
                    int lpos = l;
                    l = 1, r = (int)s[i].size() - 1;
                    while (l <= r)
                    {
                        int mid = l + r >> 1;
                        (loyalty(j, k, mid, s[i].size() - 1)) ? (r = mid - 1) : (l = mid + 1);
                    }
                    // cerr << "www " << j << ' ' << k << ": " << loyalty(j, s[i].size() - 1, s[i].size() - 1) << ' ' << loyalty(k, s[i].size() - 1, s[i].size() - 1) << '\n';
                    int rpos = r;
                    // cerr << "awa " << mx[j][lpos] << ' ' << mx[k][lpos] << ' ' << rpos << '\n';
                    if (mx[j][lpos] >= rpos || mx[k][lpos] >= rpos)
                        ++cnt;
                    else
                        cnt += 2;
                }
        cout << cnt << '\n';
    }
    else
    {
        // cerr << "idx = " << idx << '\n';
        // cerr << "cnt = " << cnt << '\n';
        for (int i = 1; i <= idx; ++i)
        {
            // cerr << "#0\n";
            for (int j = 0; j <= s[i].size(); ++j)
                for (int k = 0; k <= s[i].size(); ++k)
                    hh[j][k].clear();
            // cerr << "#1\n";
            cnt += v[i].size() * (v[i].size() - 1);
            for (int o = 0; o < v[i].size(); ++o)
            {
                // cerr << "o = " << o << '\n';
                int id = v[i][o];
                for (int j = 0; j < s[i].size(); ++j)
                    for (int k = j; k < s[i].size(); ++k)
                        cnt -= hh[j][k][make_pair(make_pair(loyalty(id, 0, j - 1), luminescent(id, 0, j - 1)), make_pair(loyalty(id, k + 1, s[i].size() - 1), luminescent(id, k + 1, s[i].size() - 1)))];
                int pos = 0;
                // cerr << "o = " << o << '\n';
                while (pos < s[i].size())
                {
                    ++hh[pos][mx[id][pos]][make_pair(make_pair(loyalty(id, 0, pos - 1), luminescent(id, 0, pos - 1)), make_pair(loyalty(id, mx[id][pos] + 1, s[i].size() - 1), luminescent(id, mx[id][pos] + 1, s[i].size() - 1)))];
                    pos = mx[id][pos] + 1;
                }
                // cerr << "o = " << o << '\n';
            }
            // cerr << "now cnt = " << cnt << '\n';
            // cerr << "#2\n";
            for (int j = 0; j <= s[i].size(); ++j)
                for (int k = 0; k <= s[i].size(); ++k)
                    hh[j][k].clear();
            for (int o = (int)v[i].size() - 1; ~o; --o)
            {
                int id = v[i][o];
                for (int j = 0; j < s[i].size(); ++j)
                    for (int k = j; k < s[i].size(); ++k)
                        cnt -= hh[j][k][make_pair(make_pair(loyalty(id, 0, j - 1), luminescent(id, 0, j - 1)), make_pair(loyalty(id, k + 1, s[i].size() - 1), luminescent(id, k + 1, s[i].size() - 1)))];
                int pos = 0;
                while (pos < s[i].size())
                {
                    ++hh[pos][mx[id][pos]][make_pair(make_pair(loyalty(id, 0, pos - 1), luminescent(id, 0, pos - 1)), make_pair(loyalty(id, mx[id][pos] + 1, s[i].size() - 1), luminescent(id, mx[id][pos] + 1, s[i].size() - 1)))];
                    pos = mx[id][pos] + 1;
                }
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}