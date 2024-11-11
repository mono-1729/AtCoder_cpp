#pragma GCC optimize ("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
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

ll pow_ll(ll x, ll n) {
    if (n == 0) return 1LL;
    ll val = pow_ll(x, n / 2);
    val *= val;
    if (n % 2 == 1) val *= x;
    return val;
}

int main() {
    ll h, w; cin >> h >> w;
    vector<string> s(h);
    rep(i,0,h) cin >> s[i];
    rep(i,0,h)rep(j,0,w) if(s[i][j] != '?') s[i][j]--;
    if(h < w){
        vector<string> t(w, string(h, ' '));
        rep(i,0,h)rep(j,0,w) t[j][i] = s[i][j];
        swap(h, w);
        s = t;
    }
    unordered_map<ll, mint> dp;
    vector<ll> pow4(16,1);
    rep(i,1,16) pow4[i] = pow4[i-1]*4;
    ll v = pow_ll(4,w)-1;
    dp[v] = 1;
    rep(i,0,h)rep(j,0,w){
        unordered_map<ll, mint> ndp;
        for(auto [key,val]: dp){
            rep(num,0,3){
                if((key/pow4[j])%4 == num || (j && (key/pow4[j-1])%4 == num)) continue;
                if(s[i][j] != '?' && s[i][j]-'0' != num) continue;
                ll nv = key;
                nv -= ((key/pow4[j])%4)*pow4[j];
                nv += num*pow4[j];
                ndp[nv] += val;
            }
        }
        swap(dp,ndp);
    }
    mint ans = 0;
    for(auto [key,val]: dp) ans += val;
    cout << ans.val() << endl;
    return 0;
}