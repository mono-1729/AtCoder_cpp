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
    ll n, x, k; cin >> n >> x >> k;
    vector<tuple<ll, ll, ll>> puc(n);
    rep(i,0,n){
        ll p, u, c; cin >> p >> u >> c;
        puc[i] = {p, u, c};
    }
    sort(puc.begin(), puc.end(), [](auto a, auto b){
        return get<2>(a) < get<2>(b);
    });
    vector<vector<ll>> dp(x+1, vector<ll>(2, 0));
    rep(i,0,n){
        auto [pp, uu, cc] = i > 0 ? puc[i-1] : make_tuple(0LL, 0LL, -1LL);
        auto [p, u, c] = puc[i];
        vector<vector<ll>> ndp(x+1, vector<ll>(2, 0));
        rep(j,0,x+1){
            chmax(ndp[j][0],dp[j][0]);
            if(cc != c) chmax(ndp[j][0],dp[j][1]);
            else chmax(ndp[j][1],dp[j][1]);
            if(j+p > x) continue;
            if(cc == c){
                chmax(ndp[j+p][1],dp[j][1]+u);
                chmax(ndp[j+p][1],dp[j][0]+u+k);
            }
            else{
                chmax(ndp[j+p][1],dp[j][1]+u+k);
                chmax(ndp[j+p][1],dp[j][0]+u+k);
            }
        }
        swap(dp, ndp);
    }
    cout << max(dp[x][0], dp[x][1]) << endl;
    return 0;
}