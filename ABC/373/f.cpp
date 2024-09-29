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
    ll n, w; cin >> n >> w;
    vector<multiset<ll>> st(w+1);
    rep(i,0,n){
        ll x, v; cin >> x >> v;
        v--;
        while(true){
            if((st[x].size() == w/x && *st[x].begin() >= v)|| v <= 0) break;
            st[x].insert(v);
            if(st[x].size() > w/x) st[x].erase(*st[x].begin());
            v -= 2;
        }
    } 
    vector<ll> dp(w+1,0), ndp(w+1,0);
    rep(i,1,w+1){
        for(auto v: st[i]){
            ndp.assign(w+1,0);
            rep(j,0,w+1){
                chmax(ndp[j], dp[j]);
                if(j+i <= w)chmax(ndp[j+i], dp[j]+v);
            }
            swap(dp,ndp);
        }
    }
    cout << dp[w] << endl;
    return 0;
}