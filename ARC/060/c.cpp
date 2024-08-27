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
    vector<ll> x(n);
    rep(i,0,n) cin >> x[i];
    ll l, q; cin >> l >> q;
    vector<vector<ll>> dp(n,vector<ll>(17));
    rep(i,0,n)dp[i][0] = (upper_bound(x.begin(), x.end(), x[i]+l) - x.begin()) -1;
    rep(j,0,16)rep(i,0,n) dp[i][j+1] = dp[dp[i][j]][j];
    rep(i,0,q){
        ll a, b; cin >> a >> b;
        if(a > b) swap(a,b);
        a--;b--;
        ll ng = 0, ok = 100000;
        while(ok - ng > 1){
            ll mid = (ok+ng)/2;
            ll x = a;
            rep(i,0,17) if(mid >> i & 1) x = dp[x][i];
            if(x >= b) ok = mid;
            else ng = mid;
        }
        cout << ok << endl;
    } 
    return 0;
}