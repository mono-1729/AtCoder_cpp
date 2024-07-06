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

using mint = modint;

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
    mint::set_mod(m);
    vector<vector<mint>> v(n + 1,vector<mint>(n + 1, 0));
    for (int i = 0; i < v.size(); i++) {
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for (int j = 1; j < v.size(); j++) {
        for (int k = 1; k < j; k++) {
            v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
        }
    }
    vector<vector<mint>> jtok(n+1,vector<mint>(n+1,0));
    jtok[1][1] = 2;
    rep(i,1,n)jtok[i+1][1] = jtok[i][1]*2;
    rep(i,1,n+1)jtok[i][1]--;
    rep(i,1,n+1)rep(j,1,n){
        jtok[i][j+1] = jtok[i][j]*jtok[i][1];
    }
    vector<mint> p2(250002,1);
    rep(i,1,250002) p2[i] = p2[i-1] * 2;
    vector<vector<mint>> dp(n,vector<mint>(n,0));
    dp[1][1] = 1;
    rep(i,1,n-1){
        rep(j,1,n){
            rep(k,1,n-i){
                dp[i+k][k] += dp[i][j] * v[n-i-1][k] * jtok[j][k] * p2[k*(k-1)/2];
            }
        }
    }
    mint ans = 0;
    rep(i,0,n){
        ans += dp[n-1][i] * jtok[i][1];
    }
    cout << ans.val() << endl;
    return 0;
}