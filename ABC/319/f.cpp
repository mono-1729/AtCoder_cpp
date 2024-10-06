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
    vector<ll> p(n), t(n), s(n), g(n);
    vector<vector<ll>> graph(n);
    unordered_map<ll, ll> drugmp, drugrev;
    ll cnt = 0;
    rep(i,1,n){
        cin >> p[i] >> t[i] >> s[i] >> g[i];
        p[i]--;
        graph[p[i]].push_back(i);
        if(t[i] == 2) drugmp[i] = cnt, drugrev[cnt++] = i;
    }
    vector<ll> max_s(1<<cnt, -INF);
    vector<pair<priority_queue<pll,vector<pll>, greater<pll>>, ll>> dp(1<<cnt);
    for(auto nv: graph[0]){
        if(t[nv] == 1) dp[0].first.push({s[nv],nv});
        else dp[0].second |= (1<<drugmp[nv]);
    }
    {
        priority_queue<pll,vector<pll>, greater<pll>>& pq = dp[0].first;
        ll start_s = 1;
        ll start_drug = dp[0].second;
        while(!pq.empty()){
            if(pq.top().first > start_s) break;
            auto [_, v] = pq.top();pq.pop();
            start_s += g[v];
            for(auto nv : graph[v]) {
                if(t[nv] == 1) pq.push({s[nv],nv});
                else start_drug |= (1<<drugmp[nv]);
            }
        }
        dp[0].second = start_drug;
        max_s[0] = start_s;
    }
    rep(bit,0,1<<cnt){
        if(max_s[bit] == -INF) continue;
        ll now_s = max_s[bit];
        auto [pq, drug] = dp[bit];
        rep(i,0,10){
            if(drug >> i & 1){
                priority_queue<pll,vector<pll>, greater<pll>> npq = pq;
                ll next_s = now_s;
                ll ndrug = drug;
                ndrug ^= (1<<i);
                ll drugid = drugrev[i];
                for(auto nv : graph[drugid]){
                    if(t[nv] == 1) npq.push({s[nv],nv});
                    else ndrug |= (1<<drugmp[nv]);
                }
                if(next_s < IINF) next_s *= g[drugrev[i]];
                chmin(next_s, IINF); 
                while(!npq.empty()){
                    if(npq.top().first > next_s) break;
                    auto [_, v] = npq.top();npq.pop();
                    next_s += g[v];
                    for(auto nv : graph[v]) {
                        if(t[nv] == 1) npq.push({s[nv],nv});
                        else ndrug |= (1<<drugmp[nv]);
                    }
                }
                if(next_s <= max_s[bit|(1<<i)]) continue;
                max_s[bit|(1<<i)] = next_s;
                dp[bit|(1<<i)] = {npq, ndrug};
            }
        }        
    }
    if(dp[(1<<cnt)-1].first.empty() && max_s[(1<<cnt)-1] != -INF) cout << "Yes" << endl;
    else cout << "No" << endl;
    // rep(i,0,1<<cnt) cout << max_s[i] << " ";
    return 0;
}