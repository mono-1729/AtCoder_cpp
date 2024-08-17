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

ll m = (1LL<<61)-1;

S op(S x1, S x2) {
    return (x1+x2)%m;
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    random_device seed_gen;
    mt19937_64 engine(seed_gen());
    ll n, q; cin >> n >> q;
    vector<ll> a(n), b(n);
    vector<ll> hash(n);
    rep(i,0,n) hash[i] = engine()>>3;
    rep(i,0,n) cin >> a[i], a[i]--;
    rep(i,0,n) cin >> b[i], b[i]--;
    segtree<S,op,e> aseg(n), bseg(n);
    rep(i,0,n){
        aseg.set(i,hash[a[i]]);
        bseg.set(i,hash[b[i]]);
    }
    //rep(i,0,n) cout << hash[i] << endl;
    rep(i,0,q){
        ll l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
        //cout << aseg.prod(l1-1,r1) << endl;
        if(aseg.prod(l1-1,r1) == bseg.prod(l2-1,r2)) cout << "Yes" << endl;
        else cout << "No" << endl; 
    }
    return 0;
}