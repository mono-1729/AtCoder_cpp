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

using S = pll;
S op(S x1, S x2) {
    return {max(x1.first, x2.first), min(x1.second, x2.second)};
} 
bool f(S x){
    return 0;
}
S e() {return {0, INF};}

int main() {
    ll n,k;cin>>n>>k;
    vector<ll> p(n);
    rep(i,0,n){
        cin>>p[i];
        p[i]--;
    }
    vector<ll> idx(n);
    rep(i,0,n)idx[p[i]] = i;
    segtree<S, op, e> seg(n);
    rep(i,0,k-1)seg.set(idx[i], {idx[i],idx[i]});
    ll ans = INF;
    rep(i,k-1,n){
        seg.set(idx[i], {idx[i],idx[i]});
        auto [ma,mi] = seg.all_prod();
        chmin(ans, ma-mi);
        // cout<<i<<" "<<ma<<" "<<mi<<endl; 
        seg.set(idx[i-k+1], {0,INF});
    }
    cout<<ans<<endl;
    return 0;
}