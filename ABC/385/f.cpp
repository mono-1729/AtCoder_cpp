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
    cout << fixed << setprecision(20);
    ll n; cin >> n;
    vector<ll> x(n), h(n);
    vector<pll> vec(n);
    rep(i,0,n) cin >> x[i] >> h[i], vec[i] = {x[i], h[i]};
    ll flg = 1;
    rep(i,0,n-1){
        auto [a,b] = vec[i];
        auto [c,d] = vec[i+1];
        if(b*c >= a*d){
            flg = 0;
            break;
        }
    }
    if(flg){
        cout << -1 << endl;
        return 0;
    }
    long double l = 0, r = (1LL << 60);

    while(true){
        long double m = (l + r) / 2;
        if((r-l)/max(1.0L,abs(l)) < 1e-18) break;
        if(m == l || m == r) break;
        flg = 1;
        rep(i,0,n-1){
            if(h[i] * x[i+1] - h[i+1] * x[i]  >= m * (x[i+1]-x[i])){
                flg = 0;
                break;
            }
        }
        if(flg) r = m;
        else l = m;
    }
    cout << l << endl;
    return 0;
}