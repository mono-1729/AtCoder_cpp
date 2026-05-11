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

using S = long long;
S op(S a, S b) {
    return max(a,b);
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    ll n; cin >> n;
    map<ll,vector<ll>> mp;
    vector<ll> rv;
    rep(i,0,n){
        ll x, r; cin >> x >> r;
        mp[x-r].push_back(x+r);
        rv.push_back(x+r);
    }
    sort(all(rv));
    rv.erase(unique(all(rv)),rv.end());
    unordered_map<ll,ll> id;
    ll m = rv.size();
    rep(i,0,m) id[rv[i]] = i;
    segtree<S,op,e> seg(m+1);
    for(auto [_,vec]: mp){
        sort(all(vec));
        for(auto r: vec){
            ll i = id[r];
            seg.set(i,seg.prod(i+1,m+1)+1);
        }
    }
    cout << seg.all_prod() << endl;
    return 0;
}