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
    ll n, m; cin >> n >> m;
    vector<ll> x(n),par(n),edge(n,0);
    vector<vector<ll>> pos(n);
    rep(i,0,n) cin >> x[i];
    rep(i,0,n) par[i] = -x[i];
    ll ans = 0;
    rep(i,0,n)pos[i].push_back(i);
    vector<tuple<ll,ll,ll>> yab;
    rep(i,0,m){
        ll a, b, y; cin >> a >> b >> y;
        a--;b--;
        yab.push_back({y,a,b});
    }
    sort(yab.begin(),yab.end());
    rep(i,0,m){
        auto [y, a, b] = yab[i];
        ll pa = par[a] < 0? a: par[a];
        ll pb = par[b] < 0? b: par[b];
        // cout << i << " " << pa << " " << pb << endl;
        if(pa != pb){
            if(pos[pa].size()>pos[pb].size())swap(pa, pb);
            par[pb] += par[pa];
            for(auto v:pos[pa]){
                pos[pb].push_back(v);
                par[v] = pb;
            }
            pos[pa].clear();
            edge[pb] += edge[pa];
            edge[pa] = 0;
        }
        edge[pb]++;
        // cout << i << " " << -par[pb] << " " << y << endl;
        if(y <= -par[pb]){
            ans += edge[pb];
            edge[pb] = 0;
        }
    }
    cout << m-ans << endl;
    return 0;
}