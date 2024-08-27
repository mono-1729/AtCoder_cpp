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

ll maxnum=2005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll n, m; cin >> n >> m;
    vector<vector<vector<ll>>> can(n, vector<vector<ll>>(n+1, vector<ll>(n,1)));
    vector<ll> l(m), r(m), x(m);
    rep(i, 0, m){
        cin >> l[i] >> r[i] >> x[i];
        l[i]--; x[i]--;
        can[l[i]][r[i]][x[i]] = 0;
    }
    rep(len,2,n+1)rep(left,0,n){
        if(left + len > n) break;
        ll right = left + len;
        rep(k, 0, n){
            can[left][right][k] &= can[left+1][right][k];
            can[left][right][k] &= can[left][right-1][k];
        }
    }
    vector<vector<mint>> dp(n,vector<mint>(n+1, 0));
    rep(i,0,n) if(can[i][i+1][i]) dp[i][i+1] = 1;
    rep(len,2,n+1)rep(left,0,n){
        if(left + len > n) break;
        ll right = left + len;
        rep(maxi,left,right){
            if(!can[left][right][maxi]) continue;
            mint res = 1;
            if(left < maxi) res *= dp[left][maxi];
            if(maxi+1 < right) res *= dp[maxi+1][right];
            res *= nCr(len-1,maxi-left);
            dp[left][right] += res;
        } 
    }
    cout << dp[0][n].val() << endl;
    return 0;
}