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
    ll h, w, y; cin >> h >> w >> y;
    vector<vector<ll>> a(h+2, vector<ll>(w+2, 0));
    rep(i,1,h+1)rep(j,1,w+1) cin >> a[i][j];
    vector<vector<ll>> dist(h+2, vector<ll>(w+2, INF));
    dist[0][0] = 0;
    priority_queue<pair<ll,pll>, vector<pair<ll,pll>>, greater<pair<ll,pll>>> pq;
    pq.push({0,{0,0}});
    vector<ll> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
    while(!pq.empty()){
        auto [d, p] = pq.top(); pq.pop();
        auto [x, y] = p;
        if(dist[x][y] < d) continue;
        rep(i,0,4){
            ll nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || nx >= h+2 || ny < 0 || ny >= w+2) continue;
            ll nd = max(d, a[nx][ny]);
            if(dist[nx][ny] > nd){
                dist[nx][ny] = nd;
                pq.push({nd, {nx, ny}});
            }
        }
    }
    vector<ll> ans(1e5+1, 0);
    rep(i,1,h+1)rep(j,1,w+1) ans[dist[i][j]]++;
    rep(i,1,y+1) ans[i] += ans[i-1];
    rep(i,1,y+1) cout << h*w - ans[i] << endl;
    return 0;
}