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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

bool solve(vector<vector<ll>> g, vector<vector<ll>> revg, vector<ll> grundy, vector<ll> in, ll pos, ll num){
    queue<ll> q;
    grundy[pos] = num;
    for(auto nv: revg[pos]){
        in[nv]--;
        if(in[nv] == 0) q.push(nv);
    }
    while(!q.empty()){
        ll v = q.front(); q.pop();
        unordered_set<ll> st;
        for(auto nv: g[v]){
            st.insert(grundy[nv]);
        }
        ll pre = 0;
        while(st.count(pre)) pre++;
        if(grundy[v] != -1){
            if(grundy[v] == pre) return 1;
            else return 0;
        }
        grundy[v] = pre;
        for(auto nv: revg[v]){
            in[nv]--;
            if(in[nv] == 0) q.push(nv);
        }
    }

}

int main() {
    ll n; cin >> n;
    vector<vector<ll>> g(n),revg(n);
    vector<ll> in(n,0), grundy(n,-1);
    rep(i,0,n){
        ll p; cin >> p;
        p--;
        g[p].push_back(i);
        revg[i].push_back(p);
        in[p]++;
    }
    queue<ll> q;
    rep(i,0,n) if(in[i] == 0) q.push(i);
    while(!q.empty()){
        ll v = q.front(); q.pop();
        unordered_set<ll> st;
        for(auto nv: g[v]){
            st.insert(grundy[nv]);
        }
        ll pre = 0;
        while(st.count(pre)) pre++;
        grundy[v] = pre;
        for(auto nv: revg[v]){
            in[nv]--;
            if(in[nv] == 0) q.push(nv);
        }
    }
    ll f = 1;
    rep(i,0,n){
        if(grundy[i] == -1){
            f = 0;
            unordered_set<ll> st;
            for(auto nv: g[i]){
                st.insert(grundy[nv]);
            }
            ll pre = 0;
            while(st.count(pre)) pre++;
            f |= solve(g, revg, grundy, in, i, pre);
            pre++;
            while(st.count(pre)) pre++;
            f |= solve(g, revg, grundy, in, i, pre);
            break;
        }
    }
    if(f) cout << "POSSIBLE" << endl;
    else cout << "IMPOSSIBLE" << endl;
    return 0;
}