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
    ll n, t, l; cin >> n >> t >> l;
    vector<vector<vector<ll>>> time(30,vector<vector<ll>>(n,vector<ll>(n,INF)));
    rep(i,1,t+1){
        ll u, v; cin >> u >> v;
        u--;v--;
        time[0][u][v] = i;
    }
    rep(i,1,30)rep(j,0,n)rep(k,0,n)rep(l,0,n) chmin(time[i][j][k], max(time[i-1][j][l], time[i-1][l][k]));
    vector<ll> now(n,INF);
    now[0] = 0;
    rep(bit,0,30){
        if(l >> bit & 1){
            vector<ll> next(n,INF);
            rep(i,0,n)rep(j,0,n) chmin(next[j], max(now[i], time[bit][i][j]));
            swap(now,next);
        }
    }
    for(auto a: now) cout << (a == INF ? -1 : a) << " ";
    cout << endl;
    return 0;
}