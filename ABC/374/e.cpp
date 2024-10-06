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

int main() {
    ll n, x; cin >> n >> x;
    vector<ll> a(n), p(n), b(n), q(n);
    rep(i,0,n) cin >> a[i] >> p[i] >> b[i] >> q[i];
    ll left = 0, right = 1e9 + 5;
    auto solve = [&](ll x_){
        ll sum = 0;
        rep(i,0,n){
            ll num = INF;
            rep(j,0,b[i]){
                chmin(num, p[i]*j + q[i]*(max(0LL, x_ - j*a[i]+b[i]-1)/b[i]));
            }
            rep(j,0,a[i]){
                chmin(num, q[i]*j + p[i]*(max(0LL, x_ - j*b[i]+a[i]-1)/a[i]));
            }
            sum += num;
        }
        return sum;
    };
    while(right - left > 1){
        ll mid = (left + right) / 2;
        // cout << mid << " " << solve(mid) << endl;
        if(solve(mid) > x) right = mid;
        else left = mid;
    }
    cout << left << endl;
    return 0;
}