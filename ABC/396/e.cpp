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
#define all(x) (x).begin(), (x).end()
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
    vector<ll> x(m), y(m), z(m);
    vector<vector<pll>> g(n);
    dsu uf(n);
    rep(i,0,m){
        cin >> x[i] >> y[i] >> z[i];
        x[i]--;y[i]--;
        g[x[i]].push_back({y[i], z[i]});
        g[y[i]].push_back({x[i], z[i]});
        uf.merge(x[i], y[i]);
    }
    bool ok = 1;
    vector<ll> ans(n);
    rep(digit, 0, 30){
        vector<ll> dist(n, -1);
        for(auto gr: uf.groups()){
            int k = gr.size();
            ll cnt = 0;
            dist[gr[0]] = 0;
            queue<ll> q;
            q.push(gr[0]);
            while(!q.empty()){
                ll v = q.front();q.pop();
                for(auto [nv, w] : g[v]){
                    w = (w>> digit) & 1;
                    if(dist[nv] != -1){
                        if(dist[nv] != (dist[v]^w)) ok = 0;
                    }else{
                        dist[nv] = dist[v]^w;
                        q.push(nv);
                    }
                }
            }
            for(auto v: gr) if(dist[v] == 1) cnt++;
            if(cnt > k-cnt){
                for(auto v: gr) dist[v] = 1-dist[v];
            }
            for(auto v: gr) ans[v] |= dist[v] << digit;
        }
    }
    if(ok){
        rep(i,0,n) cout << ans[i] << " ";
        cout << endl;
    }
    else cout << -1 << endl;
    
    return 0;
}