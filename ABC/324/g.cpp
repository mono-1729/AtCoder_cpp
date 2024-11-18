#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

template <typename T> struct merge_sort_tree {
    int N;
    std::vector<std::vector<T>> x;
    merge_sort_tree() = default;
    merge_sort_tree(const std::vector<T> &vec) : N(vec.size()) {
        x.resize(N * 2);
        for (int i = 0; i < N; i++) x[N + i] = {vec[i]};
        for (int i = N - 1; i; i--) {
            std::merge(x[i * 2].begin(), x[i * 2].end(), x[i * 2 + 1].begin(), x[i * 2 + 1].end(),
                       std::back_inserter(x[i]));
        }
    }
    int cntLess(int l, int r, T query) const {
        l += N, r += N;
        int ret = 0;
        while (l < r) {
            if (l & 1)
                ret += std::lower_bound(x[l].begin(), x[l].end(), query) - x[l].begin(), l++;
            if (r & 1)
                r--, ret += std::lower_bound(x[r].begin(), x[r].end(), query) - x[r].begin();
            l >>= 1, r >>= 1;
        }
        return ret;
    }
    int cntLesseq(int l, int r, T query) const {
        l += N, r += N;
        int ret = 0;
        while (l < r) {
            if (l & 1)
                ret += std::upper_bound(x[l].begin(), x[l].end(), query) - x[l].begin(), l++;
            if (r & 1)
                r--, ret += std::upper_bound(x[r].begin(), x[r].end(), query) - x[r].begin();
            l >>= 1, r >>= 1;
        }
        return ret;
    }
    int cntMore(int begin, int end, T query) const {
        int tot = std::max(0, std::min(end, N) - std::max(begin, 0));
        return tot - cntLesseq(begin, end, query);
    }
    int cntMoreeq(int begin, int end, T query) const {
        int tot = std::max(0, std::min(end, N) - std::max(begin, 0));
        return tot - cntLess(begin, end, query);
    }

    template <class OStream> friend OStream &operator<<(OStream &os, const merge_sort_tree &clt) {
        os << '[';
        for (int i = 0; i < clt.N; i++) os << clt.x[clt.N + i][0] << ',';
        return os << ']';
    }
};

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    ll q; cin >> q;
    vector<ll> l(q+1,0), r(q+1,0), u(q+1,0), d(q+1,0);
    l[0] = 0, r[0] = n, u[0] = n+1, d[0] = 1;
    merge_sort_tree mst(a);
    rep(i,1,q+1){
        ll t, s, x; cin >> t >> s >> x;
        if(t == 1){
            ll cnt = mst.cntMoreeq(l[s], r[s], d[s])+mst.cntLess(l[s], r[s], u[s])-(r[s]-l[s]);
            if(cnt <= x){
                cout << 0 << endl;
                continue;
            }
            ll ngr = l[s]-1, okr = r[s];
            while(okr-ngr > 1){
                ll mid = (okr+ngr)/2;
                if(mst.cntMoreeq(l[s],mid,d[s]) + mst.cntLess(l[s],mid,u[s])-(mid-l[s])<x)ngr = mid;
                else okr = mid;
            }
            l[i] = okr;
            r[i] = r[s];
            u[i] = u[s];
            d[i] = d[s];
            r[s] = okr;
            cout << cnt-x << endl;
        }
        if(t == 2){
            l[i] = l[s];
            r[i] = r[s];
            d[i] = max(d[s],min(u[s], x+1));
            u[i] = u[s];
            u[s] = d[i];
            int res = mst.cntMoreeq(l[i],r[i],d[i])+mst.cntLess(l[i],r[i],u[i])-(r[i]-l[i]);
            cout << res << endl;
        }
    }
    return 0;
}