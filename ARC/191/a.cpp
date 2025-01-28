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
    return min(x1, x2);
} 
ll border;
bool f(S x){
    return x >= border;
}
S e() {return IINF;}

int main() {
    ll n, m; cin >> n >> m;
    string s, t; cin >> s >> t;
    vector<S> vec(n);
    vector<vector<ll>> g(10);
    rep(i,0,n) vec[i] = s[i]-'0';
    rep(i,0,m) g[t[i]-'0'].push_back(i);
    segtree<S, op, e> seg(vec);
    ll last = -1;
    rrep(num,9,1){
        for(auto i : g[num]){
            border = num;
            ll r = seg.max_right<f>(0);
            // cout << num << " " << i << " " <<  r << endl;
            if(r < n){
                seg.set(r, num);
            }else{
                border = num+1;
                ll rr = seg.max_right<f>(0);
                if(rr == n && last < i) seg.set(n-1, num);
            }
            chmax(last, i);
        }
    }
    rep(i,0,n) cout << seg.get(i);
    cout << endl;
    return 0;
}