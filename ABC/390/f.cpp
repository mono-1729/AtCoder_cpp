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

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<vector<ll>> id(n+1);
    rep(i,0,n) id[a[i]].push_back(i);
    ll ans = 0;
    rep(i,0,n){
        ll l_min = -1, r_max = n;
        ll idx;
        idx = lower_bound(id[a[i]-1].begin(), id[a[i]-1].end(), i) - id[a[i]-1].begin() - 1;
        if(idx >= 0) chmax(l_min,id[a[i]-1][idx]);
        idx = lower_bound(id[a[i]].begin(), id[a[i]].end(), i+1) - id[a[i]].begin();
        if(idx < (ll)id[a[i]].size()) chmin(r_max,id[a[i]][idx]);
        idx = lower_bound(id[a[i]-1].begin(), id[a[i]-1].end(), i+1) - id[a[i]-1].begin();
        if(idx < (ll)id[a[i]-1].size()) chmin(r_max,id[a[i]-1][idx]);
        ans += (i-l_min)*(r_max-i);
    }
    cout << ans << endl;
    return 0;
}