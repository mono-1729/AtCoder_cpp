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
    return max(x1, x2);
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    int t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<ll> a(n),b(n);
        rep(i,0,n) cin>>a[i];
        rep(i,0,n) cin>>b[i];
        sort(a.begin(),a.end());
        sort(b.begin(),b.end());
        vector<vector<pll>> g(n);
        vector<vector<ll>> next(n);
        segtree<S,op,e> seg(n);
        rep(i,0,n){
            ll it = lower_bound(a.begin(),a.end(),b[i])-a.begin();
            rep(id,it-2,it+2){
                if(id>=0 && id<n)
                g[i].push_back({abs(a[id]-b[i]),id});
            }
            sort(g[i].begin(),g[i].end());
            seg.set(i,g[i][0].first);
            next[g[i][0].second].push_back(i);
        }
        bool ok = false;
        rep(i,0,n){
            if(b[0] < a[i]){
                ll num = INF;
                if(i>0) chmin(num,abs(a[i]-a[i-1]));
                if(i<n-1) chmin(num,abs(a[i]-a[i+1]));
                if(num >= b[0]) continue;
            }
            for(auto x:next[i]){
                seg.set(x,g[x][1].first);
            }
            if(a[i] > seg.all_prod()) ok = true;
            for(auto x:next[i]){
                seg.set(x,g[x][0].first);
            }
        }
        if(ok) cout << "Alice" << endl;
        else cout << "Bob" << endl;
    }
    return 0;
}