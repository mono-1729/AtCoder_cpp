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

using mint = modint1000000007;

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
    ll n, m; cin >> n >> m;
    vector<vector<tuple<ll, ll, ll>>> lrx(n+1);
    rep(i,0,m){
        ll l, r, x; cin >> l >> r >> x;
        l--;r--;
        lrx[r].push_back(make_tuple(l, r, x));
    }
    map<pll, mint> dp;
    dp[make_pair(-1, -1)] = 1;
    rep(i,0,n){
        map<pll, mint> ndp;
        for(auto [a,b] : dp){
            if(b == 0) continue;
            ll num3 = a.first, num2 = a.second;
            ndp[a] += b;
            ndp[make_pair(num3, i-1)] += b;
            ndp[make_pair(num2, i-1)] += b;
        }
        swap(dp, ndp);
        for(auto &[a,b] : dp){
            for(auto [l,r,x] : lrx[i]){
                if(x == 1){
                    if(a.second >= l) b = 0;
                }else if(x == 2){
                    if(a.second < l || a.first >= l) b = 0;
                }else{
                    if(a.first < l) b = 0;
                }
            }
        }
    }
    mint ans = 0;
    for(auto [a,b] : dp) ans += b;
    cout << ans.val() << endl;
    return 0;
}