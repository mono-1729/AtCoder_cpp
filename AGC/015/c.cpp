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
    ll n,m,q;cin>>n>>m>>q;
    vector<string> s(n);
    rep(i,0,n)cin>>s[i];
    vector<vector<ll>> possum(n+1, vector<ll>(m+1, 0)),edgesum(2*(n+1)+1, vector<ll>(2*(m+1)+1, 0));
    rep(i,0,n)rep(j,0,m){
        possum[i+1][j+1] = (s[i][j] == '1');
        if(i>0)edgesum[2*(i+1)-1][2*(j+1)] = (s[i][j] == '1' && s[i-1][j] == '1');
        if(j>0)edgesum[2*(i+1)][2*(j+1)-1] = (s[i][j] == '1' && s[i][j-1] == '1');
        if(i<n-1)edgesum[2*(i+1)+1][2*(j+1)] = (s[i][j] == '1' && s[i+1][j] == '1');
        if(j<m-1)edgesum[2*(i+1)][2*(j+1)+1] = (s[i][j] == '1' && s[i][j+1] == '1');
    }
    rep(i,0,n+1)rep(j,0,m)possum[i][j+1] += possum[i][j];
    rep(i,0,n)rep(j,0,m+1)possum[i+1][j] += possum[i][j];
    rep(i,0,2*n+3)rep(j,0,2*m+2)edgesum[i][j+1] += edgesum[i][j];
    rep(i,0,2*n+2)rep(j,0,2*m+3)edgesum[i+1][j] += edgesum[i][j];
    rep(i,0,q){
        ll u,l,d,r;cin>>u>>l>>d>>r;
        ll ans = possum[d][r] - possum[u-1][r] - possum[d][l-1] + possum[u-1][l-1];
        ans -= edgesum[2*d][2*r] - edgesum[2*u-1][2*r] - edgesum[2*d][2*l-1] + edgesum[2*u-1][2*l-1];
        cout<<ans<<endl;
    }
    return 0;
}