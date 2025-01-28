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
    ll n, x; cin >> n >> x;
    vector<ll> v(n), a(n), c(n);
    rep(i,0,n) cin >> v[i] >> a[i] >> c[i], v[i]--;
    vector<vector<ll>> dp(x+1, vector<ll>(3,0));
    rep(i,0,n){
        vector<vector<ll>> ndp(x+1, vector<ll>(3,0));
        rep(j,0,x+1){
            rep(k,0,3) chmax(ndp[j][k], dp[j][k]);
            if(j+c[i] <= x) chmax(ndp[j+c[i]][v[i]], dp[j][v[i]]+a[i]);
        }
        swap(dp,ndp);
    }
    // rep(i,0,x+1) cout << dp[n][i][0] << ' ';
    // cout << endl;
    ll now0 = 0, now1 = 0, now2 = 0;
    ll id0 = 0, id1 = 0, id2 = 0;
    ll ans = 0;
    while(true){
        if(now0 <= now1 && now0 <= now2){
            id0++;
            if(id0+id1+id2 > x) break;
            now0 = dp[id0][0];
            ans = min(now0, min(now1,now2));
        }else if(now1 <= now2){
            id1++;
            if(id0+id1+id2 > x) break;
            now1 = dp[id1][1];
            ans = min(now0, min(now1,now2));
        }else{
            id2++;
            if(id0+id1+id2 > x) break;
            now2 = dp[id2][2];
            ans = min(now0, min(now1,now2));
        }
    }
    cout << ans << endl;
    return 0;
}