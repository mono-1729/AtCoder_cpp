#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

struct S{
    ll lma, rma, ma, sum;
};
S op(S a, S b) {
    return {max(a.lma,a.sum+b.lma),max(b.rma,b.sum+a.rma),max(max(a.ma,b.ma),a.rma+b.lma),a.sum+b.sum};
} 
S e() {return {0,0,0,0};}

int main() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    ll sum = 0;
    vector<S> vec(n);
    rep(i,0,n){
        cin >> a[i];
        sum += a[i];
        if(a[i] == 0){
            vec[i] = {0,0,0,-1};
        } else vec[i] = {a[i],a[i],a[i],a[i]};
    }
    segtree<S,op,e> seg(vec);
    while(q--){
        ll i, v; cin >> i >> v;
        i--;
        sum -= a[i];
        sum += v;
        a[i] = v;
        if(v == 0) seg.set(i,{0,0,0,-1});
        else seg.set(i,{v,v,v,v});
        S res = seg.all_prod();
        cout << sum-res.ma << endl;
    }
    return 0;
}
