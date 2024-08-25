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

ll maxnum=1005;
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
    ll n; cin >> n;
    ll m = n*n;
    vector<pll> cnt(m);
    rep(i,0,m) cnt[i] = {0,i};
    vector<vector<ll>> a(n, vector<ll>(n));
    rep(i,0,n)rep(j,0,n){
        cin >> a[i][j];
        a[i][j]--;
        cnt[a[i][j]].first++;
    }
    sort(cnt.begin(), cnt.end(), greater<pll>());
    vector<ll> rev(m);
    rep(i,0,m) rev[cnt[i].second] = i;
    vector<vector<vector<mint>>> dp(n+1, vector<vector<mint>>(n+1, vector<mint>(400,0)));
    vector<vector<pll>> pos(m);
    mint ans = 0;
    auto calc = [&](pll x, pll y) -> mint {
        if(x.first > y.first || x.second > y.second) return 0;
        ll dx = y.first-x.first, dy = y.second-x.second;
        return nCr(dx+dy, dx);
    };
    rep(i,0,n)rep(j,0,n){
        rep(k,0,400){
            dp[i+1][j+1][k] += dp[i+1][j][k];
            dp[i+1][j+1][k] += dp[i][j+1][k];
        }
        if(rev[a[i][j]] < 400){
            dp[i+1][j+1][rev[a[i][j]]] += 1;
            ans += dp[i+1][j+1][rev[a[i][j]]];
        }else{
            ans++;
            for(auto p : pos[a[i][j]]) ans += calc(p, {i,j});
            pos[a[i][j]].push_back({i,j});
        }
    }
    cout << ans.val() << endl;
    return 0;
}