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

using S = long long;
S op(S x1, S x2) {
    return x1+x2;
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    ll n;cin>>n;
    vector<ll> a(n);
    rep(i,0,n) cin>>a[i];
    segtree<S, op, e> seg(1000010);
    rep(i,0,n) seg.set(a[i], seg.get(a[i])+1);
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    ll ans = 0;
    for(auto x: a){
        ll num = seg.get(x);
        ans += num*(num-1)/2;
        rep(i,1,1000010/x+1){
            //if(max(x+1,x*i)>=min(1000010LL, x*(i+1))) continue;
            ans += i*num*seg.prod(max(x+1,x*i), min(1000010LL, x*(i+1)));
        }
    }
    cout<<ans<<endl;

    return 0;
}