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
    vector<ll> x(n), y(n);
    rep(i,0,n) cin >> x[i] >> y[i];
    ll m; cin >> m;
    vector<ll> u(m), v(m);
    rep(i,0,m) cin >> u[i] >> v[i];
    vector<ll> hard(n,0), mini(n,INF);
    rep(i,0,n)rep(j,0,m){
        ll sx = x[i]+u[j], sy = y[i]+v[j], tx = x[(i+1)%n]+u[j], ty = y[(i+1)%n]+v[j];
        ll num = ty*sx-tx*sy;
        if(num < mini[i]){
            mini[i] = num;
            hard[i] = j;
        }
    }
    ll q; cin >> q;
    while(q--){
        ll a, b; cin >> a >> b;
        bool flg = true;
        rep(i,0,n){
            ll sx = x[i]+u[hard[i]], sy = y[i]+v[hard[i]], tx = x[(i+1)%n]+u[hard[i]], ty = y[(i+1)%n]+v[hard[i]];
            if((tx-sx)*(b-sy)-(ty-sy)*(a-sx) < 0) flg = false;
        }
        cout << (flg ? "Yes" : "No") << endl;
    }
    return 0;
}