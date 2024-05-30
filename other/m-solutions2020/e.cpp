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
    int n;cin>>n;
    vector<int> x(n),y(n),p(n);
    rep(i,0,n) cin>>x[i]>>y[i]>>p[i];
    vector<vector<int>> dist1(1<<n,vector<int>(n)),dist2(1<<n,vector<int>(n));
    rep(i,0,1<<n)rep(j,0,n){
        dist1[i][j] = dist2[i][j]= min(abs(x[j]),abs(y[j]));
        rep(k,0,n) if((i>>k)&1){
            chmin(dist1[i][j],abs(x[k]-x[j]));
            chmin(dist2[i][j],abs(y[k]-y[j]));
        }
    }
    vector<ll> ans(n+1,INF);
    rep(i,0,1<<n){
        int j = i;
        while(true){
            int k = i^j;
            ll sum = 0;
            rep(l,0,n) sum+=(ll)p[l]*min(dist1[j][l],dist2[k][l]);
            chmin(ans[__popcount(i)],sum);
            if(j==0)break;
            j=(j-1)&i;
        }
    }
    rep(i,0,n+1) cout<<ans[i]<<endl;
    return 0;
}