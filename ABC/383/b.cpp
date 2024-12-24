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
    ll h, w, d; cin >> h >> w >> d;
    vector<string> s(h);
    rep(i,0,h) cin >> s[i];
    ll ans = 0;
    rep(i,0,h*w)rep(j,i+1,h*w){
        ll x1 = i%w, y1 = i/w;
        ll x2 = j%w, y2 = j/w;
        if(s[y1][x1] == '#' || s[y2][x2] == '#') continue;
        ll cnt = 0;
        rep(k,0,h*w){
            ll x = k%w, y = k/w;
            if(s[y][x] == '#') continue;
            if(abs(x1-x)+abs(y1-y) <= d || abs(x2-x)+abs(y2-y) <= d){
                cnt++;
            }
        }
        chmax(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}