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
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<ll> p(n);
        rep(i,0,n) cin >> p[i];
        bool f1 = true, f2 = false;
        segtree<S, op, e> seg(n);
        rep(i,0,n){
            if(p[i] == i+1){
                if(seg.prod(0, i) == i){
                    f2 = true;
                }
            }else{
                f1 = false;
            }
            seg.set(p[i]-1, 1);
        }
        if(f1){
            cout << 0 << endl;
        }else if(f2){
            cout << 1 << endl;
        }else{
            if(p[0] == n && p[n-1] == 1){
                cout << 3 << endl;
            }else{
                cout << 2 << endl;
            }
        }
    }
    return 0;
}