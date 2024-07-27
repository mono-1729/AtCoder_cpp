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
    ll h, w; cin >> h >> w;
    ll sx, sy; cin >> sx >> sy;
    sx--;sy--;
    vector<string> c(h);
    rep(i, 0, h) cin >> c[i];
    string x; cin >> x;
    for(char a:x){
        if(a == 'U'){
            if(sx > 0 && c[sx-1][sy] == '.'){
                sx--;
            }
        }
        if(a == 'D'){
            if(sx < h-1 && c[sx+1][sy] == '.'){
                sx++;
            }
        }
        if(a == 'L'){
            if(sy > 0 && c[sx][sy-1] == '.'){
                sy--;
            }
        }
        if(a == 'R'){
            if(sy < w-1 && c[sx][sy+1] == '.'){
                sy++;
            }
        }
    }
    cout << sx+1 << " " << sy+1 << endl;
    return 0;
}