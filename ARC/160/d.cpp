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

using S = mint;
S op(S x1, S x2) {
    return x1*x2;
}
S e() {return 1;}

int main() {
    ll n, m, k; cin >> n >> m >> k;
    if(m%k != 0){
        cout << 0 << endl;
        return 0;
    }
    m /= k;
    segtree<S,op,e> fac(n*n+n); mint inv = 1;
    rep(i,1,n) inv /= i;
    rep(i,0,n*n+n) fac.set(i,(m+n-i-1));
    queue<vector<mint>> que;
    rep(_,0,n-k+1){
        vector<mint> vec(k,1);
        que.push(vec);
    }
    while(que.size() >= 2){
        vector<mint> vec1 = que.front(); que.pop();
        vector<mint> vec2 = que.front(); que.pop();
        que.push(convolution(vec1, vec2));
    }
    vector<mint> vec = que.front();
    mint ans = 0;
    rep(i,0,min(m+1,(ll)vec.size())){
        // cout << vec[i].val() << " " << (fac[i+n-1] * inv / fac[i]).val() << endl;
        ans += vec[i] * fac.prod(i,i+n-1) * inv;
    }
    cout << ans.val() << endl;
    return 0;
}