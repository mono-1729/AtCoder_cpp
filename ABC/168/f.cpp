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
    vector<ll> a(n), b(n), c(n), d(m), e(m), f(m);
    set<ll> xst, yst;
    xst.insert(0);
    yst.insert(0);
    rep(i,0,n){
        cin >> a[i] >> b[i] >> c[i];
        xst.insert(a[i]);
        xst.insert(b[i]);
        yst.insert(c[i]);
    } 
    rep(i,0,m){
        cin >> d[i] >> e[i] >> f[i];
        xst.insert(d[i]);
        yst.insert(e[i]);
        yst.insert(f[i]);
    } 
    unordered_map<ll,ll> xmp, ymp, xrev, yrev;
    ll xidx = 0;
    for(auto x: xst) xmp[x] = xidx, xrev[xidx++] = x;
    ll yidx = 0;
    for(auto y: yst) ymp[y] = yidx, yrev[yidx++] = y;
    vector<vector<vector<ll>>> wall(xidx+1, vector<vector<ll>>(yidx+1, vector<ll>(4,0)));
    rep(i,0,n){
        ll k = ymp[c[i]];
        rep(j,xmp[a[i]]+1, xmp[b[i]]+1) wall[j][k][2] = 1, wall[j][k+1][3] = 1;
    }
    rep(i,0,m){
        ll k = xmp[d[i]];
        rep(j,ymp[e[i]]+1, ymp[f[i]]+1) wall[k][j][0] = 1, wall[k+1][j][1] = 1;
    }
    ll ans = 0;
    vector<vector<ll>> reach(xidx+1, vector<ll>(yidx+1, 0));
    queue<pll> que;
    ll xmax = xidx, ymax = yidx;
    xidx = xmp[0], yidx  = ymp[0];
    que.push({xidx, yidx});que.push({xidx+1, yidx});que.push({xidx, yidx+1});que.push({xidx+1, yidx+1});
    reach[xidx][yidx] = 1;reach[xidx+1][yidx] = 1;reach[xidx][yidx+1] = 1;reach[xidx+1][yidx+1] = 1;
    while(!que.empty()){
        auto [xid, yid] = que.front(); que.pop();
        if(xid == 0 || xid == xmax || yid == 0 || yid == ymax){
            cout << "INF" << endl;
            // cout << xid << " " << yid << endl;
            return 0;
        }
        ans += (xrev[xid]-xrev[xid-1]) * (yrev[yid]-yrev[yid-1]);
        if(wall[xid][yid][0] == 0 && reach[xid+1][yid] == 0){
            que.push({xid+1, yid});
            reach[xid+1][yid] = 1;
        }
        if(wall[xid][yid][1] == 0 && reach[xid-1][yid] == 0){
            que.push({xid-1, yid});
            reach[xid-1][yid] = 1;
        }
        if(wall[xid][yid][2] == 0 && reach[xid][yid+1] == 0){
            que.push({xid, yid+1});
            reach[xid][yid+1] = 1;
        }
        if(wall[xid][yid][3] == 0 && reach[xid][yid-1] == 0){
            que.push({xid, yid-1});
            reach[xid][yid-1] = 1;
        }
    }
    cout << ans << endl;
    return 0;
}