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
    ll n,a,b;cin>>n>>a>>b;
    if(__popcount(a)%2==__popcount(b)%2){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    vector<ll> ans(1LL<<n,0);
    auto solve = [&](auto& solve,ll l,ll r,ll lnum,ll rnum,ll canuse)->void{
        // cout<<l<<" "<<r<<" "<<lnum<<" "<<rnum<<" "<<canuse<<endl;
        if(r-l==2){
            ans[l]=lnum;
            ans[l+1]=rnum;
            return;
        }
        ll bit,mid,lr;
        rep(i,0,n){
            if((lnum>>i &1)!=(rnum>>i &1)){
                bit = i;
                if(lnum>>i &1){
                    lr=0;
                    lnum^=(1LL<<i);
                }
                else{
                    lr=1;
                    rnum^=(1LL<<i);
                }
                break;
            }
        }
        mid = lnum;
        canuse^=1LL<<bit;
        rep(i,0,n){
            if(canuse>>i&1){
                mid^=1LL<<i;
                break;
            }
        } 
        solve(solve,l,(l+r)/2,lnum,mid,canuse);
        solve(solve,(l+r)/2,r,mid,rnum,canuse);
        if(lr==0) rep(i,l,(l+r)/2)ans[i]+=1LL<<bit;
        else rep(i,(l+r)/2,r)ans[i]+=1LL<<bit;
    };
    solve(solve,0,1LL<<n,a,b,(1LL<<n)-1);
    for(auto x:ans)cout<<x<<" ";
    cout<<endl;
    return 0;
}