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

ll maxnum=1000005;
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
    vector<ll> h(2*n);
    rep(i,0,2*n) cin >> h[i];
    sort(h.begin(), h.end());
    vector<mint> par(n+1, 1);
    rep(i,1,n+1) par[i] = par[i-1]*(2*i-1);
    queue<vector<mint>> q;
    mint ans = 0;
    q.push({1});
    ll now = 0;
    while(now < 2*n){
        ll r = now+1;
        while(r < 2*n && h[r] == h[now]) r++;
        vector<mint> vec((r-now)/2 + 1, 1);
        rep(i,1,(r-now)/2 + 1){
            vec[i] = par[i]*nCr(r-now, i*2);
        }
        q.push(vec);
        now = r;
    }
    while(q.size() > 1){
        vector<mint> x = q.front();q.pop();
        vector<mint> y = q.front();q.pop();
        q.push(convolution(x,y));
    }
    vector<mint> dp = q.front();
    rep(i,0,dp.size()){
        if(i%2 == 0) ans += dp[i] * par[n-i];
        else ans -= dp[i] * par[n-i];
    }
    cout << ans.val() << endl;
    return 0;
}