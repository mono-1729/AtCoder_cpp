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

using table = struct {
    vector<mint> odd;
    vector<mint> even;
};

int main() {
    ll n, m; cin >> n >> m;
    vector<int> a(n);
    rep(i,0,n) cin >> a[i];
    deque<table> dp;
    rep(i,0,n){
        vector<mint> odd(a[i]+1,0), even(1,1);
        odd[a[i]] = 1;
        dp.push_back({odd,even});
    }
    while(dp.size() >= 2){
        table t1 = dp.front();dp.pop_front();
        table t2 = dp.front();dp.pop_front();
        vector<mint> odd,even;
        vector<mint> vec = convolution(t1.odd,t2.even);
        if(vec.size() > odd.size()) odd.resize(vec.size(),0);
        rep(i,0,vec.size()) odd[i] += vec[i];

        vec = convolution(t1.even,t2.odd);
        if(vec.size() > odd.size()) odd.resize(vec.size(),0);
        rep(i,0,vec.size()) odd[i] += vec[i];

        vec = convolution(t1.odd,t2.odd);
        if(vec.size() > even.size()) even.resize(vec.size(),0);
        rep(i,0,vec.size()) even[i] += vec[i];

        vec = convolution(t1.even,t2.even);
        if(vec.size() > even.size()) even.resize(vec.size(),0);
        rep(i,0,vec.size()) even[i] += vec[i];
        
        dp.push_back({odd,even});
    }
    if(dp.front().odd.size() <= m) cout << 0 << endl;
    else cout << dp.front().odd[m].val() << endl;
    return 0;
}