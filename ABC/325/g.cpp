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
    string s; cin >> s;
    ll n = s.size();
    ll k; cin >> k;
    vector<vector<ll>> dp(n+1,vector<ll>(n+1,INF));
    auto solve = [&](auto solve, ll l, ll r) -> ll {
        if(dp[l][r] != INF) return dp[l][r];
        if(r-l <= 1) return dp[l][r] = r-l;
        ll res = INF;
        if(s[l] == 'o'){
            rep(fid,l+1,r){
                if(s[fid] == 'f' && solve(solve,fid+1,r) <= k && solve(solve,l+1,fid) == 0) res = 0;
            }
        }
        rep(mid,l+1,r) chmin(res,solve(solve, l, mid) + solve(solve, mid, r));
        // cout << l << " " << r << " " << res << endl;
        return dp[l][r] = res;
    };
    cout << solve(solve,0,n) << endl;
    return 0;
}