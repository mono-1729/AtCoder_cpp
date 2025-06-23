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
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<ll> l(n), r(n);
        rep(i,0,n) cin >> l[i] >> r[i];
        vector<vector<ll>> g(n,vector<ll>(n, 0));
        rep(i,0,n)rep(j,0,n){
            if(l[i] <= l[j] && r[i] >= r[j]){
                g[i][j] = 1;
            }
        }
        vector<ll> ans(n, 0);
        auto solve = [&](auto solve, vector<vector<ll>> gg, vector<ll> idx, ll plus) -> void {
            if(idx.size() == 0) return;
            if(idx.size() == 1){
                ans[idx[0]] = plus;
                return;
            }
            vector<ll> pre;
            vector<ll> nxt;
            vector<ll> use(idx.size(), 0);
            queue<ll> que;
            que.push(0);
            use[0] = 1;
            while(!que.empty()){
                ll v = que.front(); que.pop();
                rep(i,1,idx.size()){
                    if(use[i]) continue;
                    if(gg[v][i] == 1){
                        que.push(i);
                        use[i] = 1;
                    }
                }
            }
            rep(i,1,idx.size()){
                if(use[i]) pre.push_back(i);
                else nxt.push_back(i);
            }
            ans[idx[0]] = plus+pre.size();
            if(pre.size() > 0){
                vector<vector<ll>> ngg(pre.size(), vector<ll>(pre.size(), 0));
                rep(i,0,pre.size())rep(j,0,pre.size()){
                    ngg[i][j] = gg[pre[i]][pre[j]];
                }
                vector<ll> nidx(pre.size());
                rep(i,0,pre.size()) nidx[i] = idx[pre[i]];
                solve(solve, ngg, nidx, plus);
            }
            if(nxt.size() > 0){
                vector<vector<ll>> ngg(nxt.size(), vector<ll>(nxt.size(), 0));
                rep(i,0,nxt.size())rep(j,0,nxt.size()){
                    ngg[i][j] = gg[nxt[i]][nxt[j]];
                }
                vector<ll> nidx(nxt.size());
                rep(i,0,nxt.size()) nidx[i] = idx[nxt[i]];
                solve(solve, ngg, nidx, plus+pre.size()+1);
            }
        };
        vector<ll> idx(n);
        rep(i,0,n) idx[i] = i;
        solve(solve, g, idx, 0);
        for(auto x: ans) cout << x+1 << " ";
        cout << endl;
    }
    return 0;
}