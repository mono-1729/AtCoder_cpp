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

ll maxnum=200005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll n,m,b,w;cin>>n>>m>>b>>w;
    vector<vector<mint>> bdp(n+1,vector<mint>(m+1,0)),wdp(n+1,vector<mint>(m+1,0));
    rep(i,1,n+1)rep(j,1,m+1){
        bdp[i][j] = nCr(i*j,b);
        wdp[i][j] = nCr(i*j,w);
        rep(k,1,i+1)rep(l,1,j+1){
            if(k==i && l==j) continue;
            bdp[i][j]-=bdp[k][l]*nCr(i,k)*nCr(j,l);
            wdp[i][j]-=wdp[k][l]*nCr(i,k)*nCr(j,l);
        }
    }
    mint ans = 0;
    rep(i,1,n)rep(j,1,m)rep(k,1,n-i+1)rep(l,1,m-j+1){
        ans+=bdp[i][j]*wdp[k][l]*nCr(n,i)*nCr(n-i,k)*nCr(m,j)*nCr(m-j,l);
    }
    cout<<ans.val()<<endl;
    return 0;
}