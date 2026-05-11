#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll h, w; cin >> h >> w;
    vector<string> s(h);
    rep(i,0,h) cin >> s[i];
    vector<vector<ll>> g(h+w);
    rep(i,0,h)rep(j,0,w){
        if(s[i][j] == 'R'){
            g[i].push_back(h+j);
            g[h+j].push_back(i);
        }
    }
    ll r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    vector<ll> check(h+w,0);
    rep(i,0,h+w){
        if(check[i]) continue;
        auto dfs = [&](auto dfs, ll v) -> pll {
            pll res = {0,0};
            check[v] = 1;
            if(v < h) res.first++;
            else res.second++;
            for(auto nv: g[v]){
                if(check[nv]) continue;
                auto [p1,p2] = dfs(dfs,nv);
                res.first += p1;
                res.second += p2;
            }
            return res;
        };
        auto [n0,n1] = dfs(dfs,i);
        if(n0 == 0) c1++;
        else r1++;
        if(n1 == 0) r2++;
        else c2++;
    }
    ll f = (r1*c1 < r2*c2);
    // cout << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
    vector<ll> ch(h+w,-1);
    cout << h+w-r1-c1 << endl;
    rep(i,0,h+w){
        if(ch[i] > 0) continue;
        ll root = i;
        auto fr = [&](auto fr, ll v) -> void {
            ch[v] = i*2;
            if(f && v < h) root = v;
            if(!f && v >= h) root = v;
            for(auto nv: g[v]){
                if(ch[nv] == i*2) continue;
                fr(fr,nv);
            }
        };
        auto dfs = [&](auto dfs, ll v) -> void {
            ch[v] = i*2+1;
            for(auto nv: g[v]){
                if(ch[nv] == i*2+1) continue;
                dfs(dfs,nv);
                cout << (nv < h ? 'X': 'Y') << " ";
                if(nv < h) cout << nv+1 << " " << v-h+1 << endl;
                else cout << v+1 << " " << nv-h+1 << endl;
            }
        };
        fr(fr,i);
        dfs(dfs,root);
        // cout << "root: " << root << " " << f << endl;
    }
    return 0;
}