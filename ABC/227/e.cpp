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

ll dp[31][31][31][436];

int main() {
    string s; cin >> s;
    ll sw; cin >> sw;
    chmin(sw,435);
    ll n = 0, m = 0, l = 0;
    for(auto a : s){
        if(a == 'K') n++;
        if(a == 'E') m++;
        if(a == 'Y') l++;
    }
    dp[0][0][0][0] = 1;
    vector<ll> kid(n+1,-1), eid(m+1,-1), yid(l+1,-1);
    ll kcnt = 0, ecnt = 0, ycnt = 0;
    rep(i,0,s.size()){
        if(s[i] == 'K'){
            kcnt++;
            kid[kcnt] = i;
        }
        if(s[i] == 'E'){
            ecnt++;
            eid[ecnt] = i;
        }
        if(s[i] == 'Y'){
            ycnt++;
            yid[ycnt] = i;
        }
    } 
    rep(i,0,n+1)rep(j,0,m+1)rep(k,0,l+1)rep(cnt,0,sw+1){
        if(dp[i][j][k][cnt] == 0) continue;
        vector<ll> use(s.size()+1,0);
        rep(idx, 0, s.size()){
            if(s[idx] == 'K'){
                if(kid[i] < idx) use[idx+1]++;
            }else if(s[idx] == 'E'){
                if(eid[j] < idx) use[idx+1]++;
            }else if(s[idx] == 'Y'){
                if(yid[k] < idx) use[idx+1]++;
            }
            use[idx+1] += use[idx];
        }
        if(i < n){
            dp[i+1][j][k][cnt+use[kid[i+1]]] += dp[i][j][k][cnt];
        }
        if(j < m){
            dp[i][j+1][k][cnt+use[eid[j+1]]] += dp[i][j][k][cnt];
        }
        if(k < l){
            dp[i][j][k+1][cnt+use[yid[k+1]]] += dp[i][j][k][cnt];
        }
    }
    ll ans = 0;
    rep(i,0,sw+1) ans += dp[n][m][l][i];
    cout << ans << endl;
    return 0;
}