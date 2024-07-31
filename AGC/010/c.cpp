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
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<vector<ll>> g(n);
    ll par;
    rep(i,0,n-1){
        ll x, y; cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    rep(i,0,n)if(g[i].size() >= 2) par = i;
    if(n == 2){
        if(a[0] == a[1]) cout << "YES" << endl;
        else cout << "NO" << endl;
        return 0;
    }
    auto solve = [&](auto solve, int v, int p) -> int {
        if(g[v].size() == 1) return a[v];
        ll sum = 0;
        ll maxi = 0;
        for(auto nv: g[v]){
            if(nv == p) continue;
            int x = solve(solve, nv, v);
            sum += x, chmax(maxi, x);
        }
        if(p == -1){
            // cout << v << " " << a[v] << " " << maxi << " " << sum << endl;
            if(sum == a[v]*2 && maxi <= a[v]) return 1;
            else return -1;
        }else{
            if(a[v]*2 < sum || max(maxi,a[v]*2-sum)*2 > a[v]*2){
                cout << "NO" << endl;
                exit(0);
            }
            return a[v]*2 - sum;
        }
    };
    if(solve(solve, par, -1) == -1) cout << "NO" << endl;
    else cout << "YES" << endl;
    return 0;
}