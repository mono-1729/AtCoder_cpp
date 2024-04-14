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
    ll l,r;cin>>l>>r;
    ll ans = 0;
    vector<pll> v;
    auto solve = [&](auto& solve,ll x,ll y)->void{
        ans++;
        rrep(j,60,0){
            ll num = 1LL<<j;
            if((y/num)*num-num>=x){
                v.push_back({(y/num)*num-num,(y/num)*num});
                if((y/num)*num-num>x) solve(solve,x,(y/num)*num-num);
                if(y>(y/num)*num)solve(solve,(y/num)*num,y);
                break;
            }
        }
    };
    solve(solve,l,r);
    cout<<ans<<endl;
    sort(v.begin(),v.end());
    for(auto p: v){
        cout<<p.first<<" "<<p.second<<endl;
    }
    return 0;
}