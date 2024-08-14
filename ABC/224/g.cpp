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
    ll n, s, t, a, b; cin >> n >> s >> t >> a >> b;
    double ans = s <= t ? (t-s) * a : INF;
    ll l = 1, r = t;

    auto calcp = [&](ll border) -> double {
        double ok = t-border+1;
        double acnt = (t-border)/2.0;
        double res = (n/ok) * b + acnt * a;
        return res;
    };

    while(r-l >= 3){
        ll ml = (l*2+r)/3, mr = (l+r*2)/3;
        if(calcp(ml) <= calcp(mr)) r = mr;
        else l = ml;
    }
     
    rep(i,l,r+1) chmin(ans,calcp(i));
    cout << ans << endl;
    return 0;
}