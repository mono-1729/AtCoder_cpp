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
#define all(x) (x).begin(), (x).end()
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
    vector<ll> c(n), x(n);
    rep(i,0,n) cin >> c[i], c[i]--;
    rep(i,0,n) cin >> x[i];
    vector dp1(n, vector<ll>(n, INF)), dp2(n, vector<ll>(n, INF));
    auto get1 = [&](ll i, ll j){
        return dp1[i%n][j%n];
    };
    auto get2 = [&](ll i, ll j){
        return dp2[i%n][j%n];
    };
    rep(i,0,n) dp1[i][i] = x[c[i]]+1, dp2[i][i] = x[c[i]];
    rep(w,2,n+1)rep(l,0,n){
        ll r = (l+w-1)%n;
        if(c[l] == c[r]) chmin(dp2[l][r], get2(l,r+n-1));
        rep(j,0,w-1) chmin(dp2[l][r],get2(l,l+j)+get1(l+j+1,r));
        rep(j,1,w){
            chmin(dp1[l][r],get1(l,l+j-1)+get1(l+j,r));
        }
        chmin(dp1[l][r], dp2[l][r]+w);
    }

    ll ans = INF;
    rep(i,0,n) chmin(ans, get1(i,i+n-1));
    cout << ans << endl;
    return 0;
}