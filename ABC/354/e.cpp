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
    ll n;cin>>n;
    vector<pll> ab(n);
    rep(i,0,n){
        cin>>ab[i].first>>ab[i].second;
    }
    vector<ll> dp((1<<n),-1);
    rep(i,0,(1<<n)){
        ll turn = n-__popcount(i);
        if(turn%4==0){
            dp[i] = 1;
            rep(j,0,n){
                if(i&(1<<j)){
                    rep(k,j+1,n){
                        if(i&(1<<k)){
                            if(ab[j].first==ab[k].first || ab[j].second==ab[k].second){
                                if(dp[i^(1<<j)^(1<<k)]==0)dp[i] =0;
                            }
                        }
                    }
                }
            }
        }
        else if(turn%2==0){
            dp[i] = 0;
            rep(j,0,n){
                if(i&(1<<j)){
                    rep(k,j+1,n){
                        if(i&(1<<k)){
                            if(ab[j].first==ab[k].first || ab[j].second==ab[k].second){
                                if(dp[i^(1<<j)^(1<<k)]==1)dp[i] =1;
                            }
                        }
                    }
                }
            }
        }
    }
    if(dp[(1<<n)-1]==0)cout<<"Takahashi"<<endl;
    else cout<<"Aoki"<<endl;
    return 0;
}