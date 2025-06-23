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

S op(S a, S b) {
    return max(a,b);
} 
ll border;
bool f(S x){
    return x <= border;
}
S e() {return 0;}

int main() {
    ll n; cin >> n;
    vector<pll> ab(n);
    rep(i,0,n){
        ll a, b; cin >> a >> b;
        a--;b--;
        if(a > b) swap(a,b);
        ab[i] = {a, b};
    }
    sort(all(ab), greater<pll>());
    segtree<S,op,e> seg(2*n), dp(2*n);
    ll ans = 0;
    for(auto [a, b]: ab){
        ll x = seg.prod(0,b);
        seg.set(b, x+1);
        chmax(ans, x+1+dp.prod(b, 2*n));
        dp.set(a, x+1);
    }
    cout << ans << endl;
    return 0;
}