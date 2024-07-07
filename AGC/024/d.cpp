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
    ll n; cin >> n;
    vector<unordered_set<ll>> g(n);
    rep(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--;b--;
        g[a].insert(b);
        g[b].insert(a);
    }
    vector<vector<int>> dist(n,vector<int>(n,IINF));
    rep(i,0,n){
        dist[i][i] = 0;
        for(auto a: g[i]) dist[i][a] = 1;
    }
    rep(k,0,n)rep(i,0,n)rep(j,0,n){
        chmin(dist[i][j],dist[i][k] + dist[k][j]);
    }
    int p1 = 0, p2 = 1;
    rep(i,0,n)rep(j,0,n){
        if(dist[p1][p2] < dist[i][j]) p1 = i, p2 = j;
    }
    ll c1 = -1, c2 = -1;
    if(dist[p1][p2]%2 == 0){
        rep(i,0,n){
            if(dist[p1][i] == dist[i][p2] && dist[p1][i] + dist[i][p2] == dist[p1][p2]) c1 = i;
        }
    }else{
        rep(i,0,n)rep(j,0,n){
            if(dist[p1][i] == dist[j][p2] && dist[i][j] == 1 && dist[p1][i] + dist[i][j] + dist[j][p2] == dist[p1][p2]){
                c1 = i, c2 = j;
            }
        }
        n++;
    }
    vector<ll> num(n,1);
    auto solve = [&](auto solve, ll v, ll par, ll d) ->void {
        if(par == -1) chmax(num[0],g[v].size());
        else chmax(num[d],g[v].size()-1);
        for(auto nv:g[v]){
            if(nv == par) continue;
            solve(solve, nv, v, d+1);
        }
    };
    ll ans = INF;
    if(dist[p1][p2]%2 == 0){
        for(auto x:g[c1]){
            num.assign(n,1);
            ll cnt = 2;
            solve(solve,x,c1,0);
            solve(solve,c1,x,0);
            for(auto l:num) cnt*=l;
            chmin(ans,cnt);
        }
        num.assign(n,1);
        ll cnt = 1;
        solve(solve,c1,-1,0);
        for(auto l:num) cnt*=l;
        chmin(ans,cnt);
    }else{
        solve(solve,c1,c2,0);
        solve(solve,c2,c1,0);
        ans = 2;
        for(auto x:num) ans*=x;
    }
    cout << (dist[p1][p2]+2)/2 << " " << ans << endl;
    return 0;
}