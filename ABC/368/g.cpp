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

using S = ll;
S op(S x1, S x2) {
    return x1+x2;
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i];
    segtree<S, op, e> seg(a);
    set<ll> b2;
    rep(i,0,n){
        if(b[i] >= 2) b2.insert(i);
    }
    ll q; cin >> q;
    rep(i,0,q){
        ll t, x, y; cin >> t >> x >> y;
        x--;
        if(t == 1){
            a[x] = y;
            seg.set(x, y);
        }else if(t == 2){
            if(b2.count(x)) b2.erase(x);
            b[x] = y;
            if(y >= 2) b2.insert(x);
        }else{
            ll ans = 0;
            ll now = x;
            auto it = b2.lower_bound(x);
            while(it != b2.end()){
                ll nx = *it;
                if(nx >= y) break;
                ans += seg.prod(now, nx);
                ans = max(ans + a[nx], ans * b[nx]);
                now = nx+1;
                it++;
            }
            ans += seg.prod(now, y);
            cout << ans << endl;
        }
    }
    return 0;
}