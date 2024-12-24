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
    vector<ll> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
    vector<vector<ll>> dist(h, vector<ll>(w, INF));
    queue<pll> q;
    rep(i,0,h)rep(j,0,w){
        if(s[i][j] == 'H'){
            q.push({i, j});
            dist[i][j] = 0;
        }
    }
    while(!q.empty()){
        auto [y, x] = q.front(); q.pop();
        rep(i,0,4){
            ll nx = x+dx[i], ny = y+dy[i];
            if(nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            if(s[ny][nx] == '#') continue;
            if(dist[ny][nx] > dist[y][x]+1){
                dist[ny][nx] = dist[y][x]+1;
                q.push({ny, nx});
            }
        }
    }
    ll ans = 0;
    rep(i,0,h)rep(j,0,w){
        if(dist[i][j] <= d) ans++;
    }
    cout << ans << endl;
    return 0;
}