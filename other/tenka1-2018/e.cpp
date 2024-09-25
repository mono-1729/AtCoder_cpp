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
    ll h, w; cin >> h >> w;
    vector<vector<ll>> s(h+w,vector<ll>(h+w,0));
    vector<segtree<S,op,e>> rowseg(h+w,segtree<S,op,e>(h+w)), colseg(h+w,segtree<S,op,e>(h+w));
    rep(i,0,h)rep(j,0,w){
        char x; cin >> x;
        if(x == '#'){
            s[i+j][i-j+w] = 1;
            rowseg[i+j].set(i-j+w, rowseg[i+j].get(i-j+w)+1);
            colseg[i-j+w].set(i+j, colseg[i-j+w].get(i+j)+1);
        }
    }
    ll ans = 0;
    rep(u,0,h+w)rep(l,0,h+w)rep(n,1,h+w){
        ll d = u+n, r = l+n;
        if(d >= h+w || r >= h+w) break;
        if(s[u][l] && s[d][l]) ans += colseg[r].prod(u,d+1);
        if(s[u][r] && s[d][r]) ans += colseg[l].prod(u,d+1);
        if(n >= 3){
            if(s[d][l] && s[d][r]) ans += rowseg[u].prod(l+1,r);
            if(s[u][l] && s[u][r]) ans += rowseg[d].prod(l+1,r);
        }
    }
    cout << ans << endl;
    return 0;
}