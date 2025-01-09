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

ll M = 100005, MX = M*2;

using S = long long;
S op(S x1, S x2) {
    return x1+x2;
}
S e() {return 0;}

int main() {
    ll n; cin >> n;
    vector<vector<ll>> pos(MX);
    rep(i,0,n){
        ll x, y; cin >> x >> y;
        pos[x+y].push_back(x-y+M);
    }
    ll q; cin >> q;
    vector<ll> a(q), b(q), k(q);
    rep(i,0,q){
        ll x, y;
        cin >> x >> y >> k[i];
        a[i] = x+y, b[i] = x-y+M;
    }

    vector<ll> ng(q,-1), ok(q,MX);
    rep(_,0,18){
        vector<ll> mid(q), num(q);
        vector<tuple<ll,ll,ll>> query;
        rep(i,0,MX)for(auto y: pos[i]){
            query.push_back({i,0,y});
        }
        rep(i,0,q){
            mid[i] = (ok[i]+ng[i])/2;
            query.push_back({a[i]-mid[i],-1,i});
            query.push_back({a[i]+mid[i],1,i});
        }
        sort(query.begin(), query.end());
        segtree<S,op,e> seg(MX);
        for(auto [x, type, y] : query){
            if(type == 0) seg.set(y,seg.get(y)+1);
            else{
                num[y] += type*seg.prod(max(0LL,b[y]-mid[y]), min(MX,b[y]+mid[y]+1));
            }
        }
        rep(i,0,q){
            if(num[i] >= k[i]) ok[i] = mid[i];
            else ng[i] = mid[i];
        }
    }
    rep(i,0,q) cout << ok[i] << endl;
    return 0;
}