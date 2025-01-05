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
    vector<string> s(h);
    rep(i, 0, h) cin >> s[i];
    ll sx, sy, gx, gy;
    rep(i, 0, h) rep(j, 0, w){
        if(s[i][j] == 'S'){
            sx = i;
            sy = j;
        }
        if(s[i][j] == 'G'){
            gx = i;
            gy = j;
        }
    }
    vector<vector<ll>> dist0(h, vector<ll>(w, INF)), dist1(h, vector<ll>(w, INF));
    dist0[sx][sy] = 0, dist1[sx][sy] = 0;
    queue<tuple<ll, ll, ll>> q;
    q.push({sx, sy,0});
    q.push({sx, sy,1});
    vector<ll> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
    while(!q.empty()){
        auto [x, y, div] = q.front(); q.pop();
        rep(i, 0, 4){
            if(div != i%2) continue;
            ll nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if(s[nx][ny] == '#') continue;
            if(div == 0){
                if(dist0[nx][ny] != INF) continue;
                dist0[nx][ny] = dist1[x][y]+1;
                q.push({nx, ny, 1});
            }
            if(div == 1){
                if(dist1[nx][ny] != INF) continue;
                dist1[nx][ny] = dist0[x][y] + 1;
                q.push({nx, ny, 0});
            }
        }
    }
    if(dist0[gx][gy] == INF && dist1[gx][gy] == INF){
        cout << -1 << endl;
    }else{
        cout << min(dist0[gx][gy], dist1[gx][gy]) << endl;
    }
    return 0;
}