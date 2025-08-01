#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
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
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    } 
    ll s = 0, t = 0;
    ll maxd = 0;
    rep(_,0,2){
        queue<ll> q;
        vector<ll> dist(n,INF);
        dist[s] = 0;
        q.push(s);
        while(!q.empty()){
            ll v = q.front(); q.pop();
            t = v;
            for(auto nv: g[v]){
                if(dist[nv] == INF){
                    dist[nv] = dist[v]+1;
                    q.push(nv);
                }
            }
        }
        maxd = dist[t];
        // cout << t << " " << dist[t] << endl;
        swap(s,t);
    }
    mint ans = (mint)(maxd)/2;
    vector<tuple<ll,ll,ll>> vec;
    rep(_,0,2){
        queue<ll> q;
        vector<ll> dist(n,INF);
        dist[s] = 0;
        q.push(s);
        while(!q.empty()){
            ll v = q.front(); q.pop();
            for(auto nv: g[v]){
                if(dist[nv] == INF){
                    dist[nv] = dist[v]+1;
                    q.push(nv);
                }
            }
        }
        rep(i,0,n){
            if(i == t) continue;
            vec.push_back({dist[i],s,i});
        }
        swap(s,t);
    }
    vector<ll> col(n,-1);
    col[s] = 0, col[t] = 1;
    sort(all(vec), greater<tuple<ll,ll,ll>>());
    mint p = (mint)1/2;
    rep(i,0,2*n-2){
        auto [d,start,id] = vec[i];
        if(col[id] != -1){
            if(col[id] == col[start]){
                ans += d*p;
                break;
            }else continue;
        }
        col[id] = 1-col[start];
        p /= 2;
        ans += p*d;
        // cout << p << " " << ans << endl;
    }
    // cout << ans << endl;
    rep(i,0,n) ans *= 2;
    cout << ans.val() << endl;
    return 0;
}