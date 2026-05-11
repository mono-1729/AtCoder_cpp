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
constexpr ll MOD = 1000000007;
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    map<tuple<ll,vector<vector<ll>>,ll>,ll> mp;
    vector<vector<ll>> graph;
    {
        ll id = 0;
        rep(i,1,1<<h){
            vector<ll> v1;
            rep(b,0,h) if(i>>b&1) v1.push_back(b);
            vector<vector<ll>> group;
            auto dfs = [&](auto& dfs, ll bit, ll gcnt, ll preg) -> void {
                if(bit == __builtin_popcountll(i)){
                    rep(k,0,gcnt) mp[{i,group,k}] = id++;
                    return;
                }
                if(bit > 0 && v1[bit]-1 == v1[bit-1]){
                    group[preg].push_back(v1[bit]);
                    dfs(dfs, bit+1, gcnt, preg);
                    group[preg].pop_back();
                    return;
                }
                rep(ng,0,gcnt+1){
                    if(ng == gcnt){
                        group.push_back({v1[bit]});
                        dfs(dfs, bit+1, gcnt+1, ng);
                        group.pop_back();
                    }else{
                        group[ng].push_back(v1[bit]);
                        dfs(dfs, bit+1, gcnt, ng);
                        group[ng].pop_back();
                    }
                }
            };
            dfs(dfs,0,0,-1);
        }
    }
    graph.resize(mp.size());
    for(auto p: mp){
        auto [tu,id] = p;
        auto [i,j,k] = tu;
        rep(next,1,1<<h){
            vector<vector<ll>> g(2*h);
            vector<ll> check(2*h,-1);
            rep(bit,0,h-1) if((next>>bit&1) && (next>>(bit+1)&1)){
                g[h+bit].push_back(h+bit+1);
                g[h+bit+1].push_back(h+bit);
            }
            rep(bit,0,h){
                if(!((i&next)>>bit&1)) continue;
                g[bit].push_back(bit+h);
                g[bit+h].push_back(bit);
            }
            for(auto gr: j){
                rep(ii,0,gr.size()-1){
                    g[gr[ii]].push_back(gr[ii+1]);
                    g[gr[ii+1]].push_back(gr[ii]);
                }
            }
            vector<vector<ll>> nj;
            ll nk = -1;
            rep(s,h,2*h){
                if(check[s] != -1) continue;
                if(!(next>>(s-h)&1)) continue;
                queue<ll> q;
                q.push(s);
                check[s] = nj.size();
                nj.push_back({s-h});
                while(!q.empty()){
                    ll v = q.front(); q.pop();
                    if(v == j[k][0]) nk = nj.size()-1;
                    for(auto nv: g[v]){
                        if(check[nv] == -1){
                            check[nv] = check[v];
                            if(nv >= h) nj.back().push_back(nv-h);
                            q.push(nv);
                        }
                    }
                }
            }
            for(auto& vv: nj) sort(all(vv));
            
            if(nk != -1) graph[id].push_back(mp[{next,nj,nk}]);
        }
    }
    vector<mint> dp(mp.size());
    dp[mp[{1,{{0}},0}]] = 1;
    rep(_,0,w+1){
        vector<mint> ndp(dp.size());
        rep(i,0,dp.size())for(auto j: graph[i]){
            ndp[j] += dp[i];
        }
        swap(dp,ndp);
    }
    cout << dp[mp[{1<<(h-1),{{h-1}},0}]].val() << endl;
    return 0;
}