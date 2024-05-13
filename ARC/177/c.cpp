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
    vector<ll> dx = {1,0,-1,0};
    vector<ll> dy = {0,1,0,-1};
    ll n;cin>>n;
    vector<string> c(n);
    rep(i,0,n)cin>>c[i];
    ll ans = 0;
    vector<vector<ll>> dist(n,vector<ll>(n,INF));
    deque<pll> q;
    q.push_back({0,0});
    if(c[0][0] == 'R') dist[0][0] = 0;
    else dist[0][0] = 1;
    while(!q.empty()){
        auto [x,y] = q.front();q.pop_front();
        rep(i,0,4){
            ll nx = x+dx[i];
            ll ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
            ll add = 0;
            if(c[nx][ny] == 'B') add = 1;
            if(dist[nx][ny]==INF || dist[nx][ny]>dist[x][y]+add){
                dist[nx][ny] = dist[x][y]+add;
                if(add == 0) q.push_front({nx,ny});
                else q.push_back({nx,ny});
            }
        }
    }
    ans+=dist[n-1][n-1];
    dist = vector<vector<ll>>(n,vector<ll>(n,INF));
    q.push_back({0,n-1});
    if(c[0][n-1] == 'B') dist[0][n-1] = 0;
    else dist[0][n-1] = 1;
    while(!q.empty()){
        auto [x,y] = q.front();q.pop_front();
        rep(i,0,4){
            ll nx = x+dx[i];
            ll ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
            ll add = 0;
            if(c[nx][ny] == 'R') add = 1;
            if(dist[nx][ny]==INF || dist[nx][ny]>dist[x][y]+add){
                dist[nx][ny] = dist[x][y]+add;
                if(add == 0) q.push_front({nx,ny});
                else q.push_back({nx,ny});
            }
        }
    }
    ans+=dist[n-1][0];
    cout<<ans<<endl;
    return 0;
}