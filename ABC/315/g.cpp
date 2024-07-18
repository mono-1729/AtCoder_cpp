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

// 拡張ユークリッドの互除法
// ap+bq=gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします。
cpp_int extGCD(cpp_int a, cpp_int b, cpp_int &p, cpp_int &q){
    if (b == 0) {
        p = 1;
        q = 0;
        return a;
    }
    cpp_int d = extGCD(b, a%b, q, p);
    q -= a/b*p;
    return d;
}


int main() {
    cpp_int n,a,b,c,x_; cin >> n >> a >> b >> c >> x_;
    x_ -= a+b+c;
    cpp_int ans = 0;
    cpp_int bc_gcd = gcd(b,c);
    b /= bc_gcd;
    c /= bc_gcd;
    rep(i,0,n){
        if(a*i > x_) break;  
        cpp_int x = x_ - a*i;
        if(x%bc_gcd != 0) continue;
        x /= bc_gcd;
        cpp_int p = 0, q = 0;
        extGCD(b,c,p,q);
        p *= x, q*= x;
        cpp_int num;
        if(p>=0) num = -(p/c);
        else num = -((p-c+1)/c);
        p += num * c; q -= num * b;
        if(p >= n || q < 0) continue;
        cpp_int l = 0, r = (n-p-1)/c;
        chmin(r,q/b);
        if(q >= n) l = (q-n)/b +1;
        ans += max((cpp_int)0,r-l+1);
        // cout << i << ' ' << ans << ' ' << l << ' ' << r << endl;
    }
    cout << ans << endl;
    return 0;
}