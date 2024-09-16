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

int main() {
    ll n; cin >> n;
    vector<pll> vec;
    vector<ll> x(n), p(n);
    rep(i,0,n) cin >> x[i];
    rep(i,0,n) cin >> p[i];

    rep(i,0,n) vec.push_back({x[i],p[i]});
    sort(vec.begin(), vec.end());
    vector<ll> sum(n+1,0);
    rep(i,0,n) sum[i+1] += sum[i] + vec[i].second;

    ll q; cin >> q;
    while(q--){
        ll l, r; cin >> l >> r;
        ll idx = upper_bound(vec.begin(), vec.end(), make_pair(r,INF)) - vec.begin();
        ll ans = sum[idx];
        idx = upper_bound(vec.begin(), vec.end(), make_pair(l-1,INF)) - vec.begin();
        ans -= sum[idx];
        cout << ans << endl;
    }
    return 0;
}