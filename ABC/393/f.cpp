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

using S = long long;
S op(S x1, S x2) {
    return max(x1,x2);
} 
ll border;
bool f(S x){
    return x <= border;
}
S e() {return 0;}

int main() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<vector<pll>> query(n);
    rep(i,0,q){
        ll r, x; cin >> r >> x;
        r--;
        query[r].push_back({i,x});
    }
    vector<S> vec(n+1,INF);
    vec[0] = 0;
    segtree<S,op,e> seg(vec);
    vector<ll> ans(q);
    rep(i,0,n){
        border = a[i]-1;
        ll x = seg.max_right<f>(0);
        if(a[i] < seg.get(x)) seg.set(x, a[i]);
        for(auto [j,num]: query[i]){
            border = num;
            ans[j] = seg.max_right<f>(0)-1;
        }
    }
    rep(i,0,q) cout << ans[i] << endl;
    return 0;
}