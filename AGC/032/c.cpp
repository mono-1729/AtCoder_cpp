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
    int n,m; cin >> n >> m;
    vector<unordered_set<ll>> g(n);
    rep(i,0,m){
        ll a, b; cin >> a >> b;
        a--;b--;
        g[a].insert(b);
        g[b].insert(a);
    }
    int n0 = 0;
    int cnt = 0;
    queue<ll> pos;
    rep(i,0,n){
        if(g[i].size()%2 == 1){
            cout << "No" << endl;
            return 0;
        }
        if(g[i].size() == 2) pos.push(i);
    }
    while(cnt < 3 && !pos.empty()){
        ll p = pos.front();pos.pop();
        if(g[p].size() == 0) continue;
        ll p1 = *g[p].begin();g[p].erase(p1);g[p1].erase(p);
        ll p2 = *g[p].begin();g[p].erase(p2);g[p2].erase(p);
        if(g[p1].count(p2)){
            cnt++;
            g[p1].erase(p2);
            g[p2].erase(p1);
            if(g[p1].size() == 2) pos.push(p1);
            if(g[p2].size() == 2) pos.push(p2);
            if(g[p1].size() == 0) n0++;
            if(g[p2].size() == 0) n0++;
        }
        else{
            g[p1].insert(p2);
            g[p2].insert(p1);
        }
        n0++;
    }
    if(cnt < 3 && n0 == n) cout << "No" << endl;
    else cout << "Yes" << endl; 
    return 0;
}