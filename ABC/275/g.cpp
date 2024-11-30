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
    cout << fixed << setprecision(15);
    double ans = 0;
    ll n; cin >> n;
    vector<tuple<ll,ll,ll>> avec, bvec;
    rep(i,0,n){
        ll a, b, c; cin >> a >> b >> c;
        chmax(ans, (double)c/max(a,b));
        if(a > b) avec.push_back({a,b,c});
        else if (a < b) bvec.push_back({a,b,c});
    }
    sort(avec.begin(), avec.end(), [](auto x, auto y){
        auto [a1, b1, c1] = x;
        auto [a2, b2, c2] = y;
        return (double)(a1+b1)/c1 < (double)(a2+b2)/c2;
    });
    sort(bvec.begin(), bvec.end(), [](auto x, auto y){
        auto [a1, b1, c1] = x;
        auto [a2, b2, c2] = y;
        return (double)(a1+b1)/c1 < (double)(b2+a2)/c2;
    });
    if(avec.size() && bvec.size()){
        for(auto [a1, b1, c1] : avec){
            auto [a2, b2, c2] = *bvec.begin();
            double k = (double)(a1-b1) / (b2-a2);
            chmax(ans, (double)(c1+k*c2)/(a1+k*a2));
        }
        for(auto [a2, b2, c2] : bvec){
            auto [a1, b1, c1] = *avec.begin();
            double k = (double)(a1-b1) / (b2-a2);
            chmax(ans, (double)(c1+k*c2)/(a1+k*a2));
        }
    }
    cout << ans << endl;
    return 0;
}