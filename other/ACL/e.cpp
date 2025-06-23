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

struct S{
    mint p;
    mint d;
    mint cnt;
};
S op(S a, S b) {
    return {a.p+b.p, a.d+b.d, a.cnt+b.cnt};
} 
bool f(S x){
    return 1;
}
S e() {return {0,0};}

int main() {
    ll n, k; cin >> n >> k;
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i], p[i]--;
    mint ans = 0;
    vector<mint> powk(n+1,1), divk(n+1,1);
    mint div2 = (mint)1/2;
    mint kk = mint(k-1)/k;
    rep(i,0,n){
        powk[i+1] = powk[i]*kk;
        divk[i+1] = divk[i]/kk;
    }
    segtree<S,op,e> seg(n);
    rep(i,0,n){
        ll x = max(i-k+1, 0LL);
        S l = seg.prod(0,p[i]), r = seg.prod(p[i],n);
        ans += l.d*powk[x]*div2;
        ans += r.d*powk[x]*div2;
        ans += r.cnt-r.d*powk[x];
        seg.set(p[i],{powk[x],divk[x],1});
    }
    cout << ans.val() << endl;
    return 0;
}