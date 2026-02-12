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
struct S {
    mint n0;
    mint n1;
    mint n0a;
    mint n1a;
};
S op(S a, S b) {
    if(a.n0 == -1) return b;
    else if(b.n0 == -1) return a;
    return {
        b.n0a == 0 ? a.n0a : a.n0 + a.n0a + a.n0a*(b.n0+b.n1),
        a.n1a == 0 ? b.n1 : a.n1 + a.n1a + a.n1a*(b.n0+b.n1),
        a.n0a == 0 ? b.n0a : a.n0a*(b.n0a+b.n1a),
        a.n1a == 0 ? b.n1a : a.n1a*(b.n0a+b.n1a)
    };
} 
S e() {return {-1,-1,-1,-1};}

int main() {
    ll n, q; cin >> n >> q;
    string s; cin >> s;
    vector<S> vec(n);
    unordered_map<char,S> mp;
    mp['1'] = {0,0,0,1};
    mp['0'] = {0,0,1,0};
    mp['?'] = {0,0,1,1};
    rep(i,0,n) vec[i] = mp[s[i]];
    segtree<S,op,e> seg(vec);
    {
        auto [a,b,cc,d] = seg.all_prod();
        cout << (a+b+cc+d).val() << endl;
        cout << a.val() << " " << b.val() << " " << cc.val() << " " << d.val() << endl;

    }
    while(q--){
        ll x; char c; cin >> x >> c;
        x--;
        seg.set(x,mp[c]);
        auto [a,b,cc,d] = seg.all_prod();
        cout << (a+b+cc+d).val() << endl;
        cout << a.val() << " " << b.val() << " " << cc.val() << " " << d.val() << endl;
    }
    return 0;
}