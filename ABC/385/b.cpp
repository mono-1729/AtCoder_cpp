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
    ll h, w, x, y; cin >> h >> w >> x >> y;
    vector<string> s(h);
    rep(i,0,h) cin >> s[i];
    x--; y--;
    vector<ll> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    unordered_map<char, ll> cmp;
    cmp['U'] = 0;
    cmp['D'] = 1;
    cmp['L'] = 2;
    cmp['R'] = 3;
    string t; cin >> t;
    ll ans = 0;
    for(auto c : t){
        ll nx = x + dx[cmp[c]];
        ll ny = y + dy[cmp[c]];
        if(nx < 0 || nx >= h || ny < 0 || ny >= w || s[nx][ny] == '#') continue;
        x = nx;
        y = ny;
        if(s[x][y] == '@'){
            ans++;
            s[x][y] = '.';
        }
    }
    cout << x+1 << " " << y+1 << " " << ans << endl;
    return 0;
}