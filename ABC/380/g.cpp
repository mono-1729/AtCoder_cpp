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
    ll n, k; cin >> n >> k;
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i], p[i]--;
    vector<ll> num(n,0);
    segtree<S, op, e> segma(n), seg(n);
    rrep(i,n-1,0){
        num[i] = segma.prod(0,p[i]);
        segma.set(p[i], 1);
    }
    mint inv2 = mint(2).inv(), inv = mint(n-k+1).inv();
    mint plus = k*(k-1)*inv2*inv2;
    mint ans = 0;
    mint rsum = 0, lsum = 0;
    mint now = 0;
    rep(i,0,n-k) lsum += num[i];
    rrep(i,n-1,n-k) seg.set(p[i], 1);
    ll idx = n-k-1;
    while(true){
        mint xx = lsum + rsum + plus + now;
        // cout << lsum.val() << " " << rsum.val() << " " << plus.val() << " " << now.val() << endl;
        ans += xx*inv;
        if(idx < 0) break;
        seg.set(p[idx+k], 0);
        now += seg.prod(p[idx+k],n);
        now += num[idx] - seg.prod(0,p[idx]);
        now -= num[idx+k];
        seg.set(p[idx], 1);
        lsum -= num[idx];
        rsum += num[idx+k];
        idx--;
    }
    cout << ans.val() << endl;
    return 0;
}