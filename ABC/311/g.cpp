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
    ll n,m;cin>>n>>m;
    vector<vector<ll>> a(n, vector<ll>(m)),sum(n+1, vector<ll>(m+1));
    rep(i, 0, n) rep(j, 0, m){
        cin>>a[i][j];
        sum[i+1][j+1] = a[i][j];
    }
    rep(i,0,n+1)rep(j,0,m) sum[i][j+1]+=sum[i][j];
    rep(i,0,n)rep(j,0,m+1) sum[i+1][j]+=sum[i][j];
    auto calcsum= [&](ll u,ll d,ll l,ll r){
        return sum[r+1][d+1]-sum[r+1][u]-sum[l][d+1]+sum[l][u];
    };
    vector<vector<ll>> field(n,vector<ll>(m,0));
    ll ans = 0;
    rrep(min_num,300,1){
        rep(i,0,n)rep(j,0,m)if(a[i][j]==min_num)field[i][j]=min_num;
        vector<ll> h(m+1,0);
        rep(d,0,n){
            rep(j,0,m){
                if(field[d][j]>=min_num) h[j]++;
                else h[j]=0;
            }
            stack<pll> stk;
            stk.push({-1,-1});
            rep(i,0,m+1){
                ll lidx = i;
                while(stk.top().first>h[i]){
                    auto p = stk.top();stk.pop();
                    lidx = p.second;
                    chmax(ans,min_num*calcsum(p.second,i-1,d-p.first+1,d));
                }
                stk.push({h[i],lidx});
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}