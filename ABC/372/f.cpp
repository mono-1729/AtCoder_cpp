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
    ll n, m, k; cin >> n >> m >> k;
    deque<mint> dp;
    rep(i,0,n) dp.push_back((i ? 0 : 1));
    vector<ll> u(m), v(m);
    rep(i,0,m){
        cin >> u[i] >> v[i];
        u[i]--;v[i]--;
    }
    rep(i,0,k){
        vector<pair<ll,mint>> add(m);
        rep(j,0,m) add[j] = {v[j], dp[u[j]]};
        dp.push_front(dp.back()); dp.pop_back();
        for(auto [x,y] : add) dp[x] += y;
    }
    mint ans = 0;
    rep(i,0,n) ans += dp[i];
    cout << ans.val() << endl;
    return 0;
}