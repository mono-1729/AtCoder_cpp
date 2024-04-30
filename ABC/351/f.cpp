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

using S = struct 
{
    ll num;
    ll sum;
};

S op(S x1, S x2) {
    S res;
    res.num = x1.num + x2.num;
    res.sum = x1.sum + x2.sum;
    return res;
} 
bool f(S x){
    return 1;
}
S e() {return {0,0};}

int main() {
    ll n;cin>>n;
    vector<ll> a(n);
    rep(i,0,n)cin>>a[i];
    map<ll,ll> mp;
    rep(i,0,n){
        mp[a[i]]=1;
    }
    unordered_map<ll,ll> mp2;
    ll cnt = 0;
    for(auto x:mp){
        mp2[x.first]=cnt;
        cnt++;
    }
    vector<S> v(cnt,{0,0});
    segtree<S, op, e> seg(v);
    ll ans = 0;
    rep(i,0,n){
        ll x = mp2[a[i]];
        S s = seg.prod(0,x);
        ans+=s.num*a[i]-s.sum;
        seg.set(x,{seg.get(x).num+1,seg.get(x).sum+a[i]});
    }
    cout<<ans<<endl;
    return 0;
}