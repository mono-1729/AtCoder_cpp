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
    vector<vector<pll>> g(n);
    rep(i,0,m){
        ll u,v,s;cin>>u>>v>>s;
        u--;v--;
        g[u].push_back({v,s});
        g[v].push_back({u,s});
    }
    vector<ll>plus(n,-INF),minus(n,INF);
    plus[0]=0;
    queue<tuple<ll,ll,ll>> q;
    q.push({0,0,1});
    vector<ll> check(n,0);
    check[0]=1;
    ll mi = 1,ma = INF;
    while(!q.empty()){
        ll v,num,sign;tie(v,num,sign)=q.front();q.pop();
        sign = -sign;
        for(auto p:g[v]){
            ll nv = p.first, s = p.second;
            ll nnum = s-num;
            if(sign==1){
                if(check[nv]==0){
                    plus[nv]=nnum;
                    chmax(mi,-nnum+1);
                    check[nv]=1;
                    q.push({nv,nnum,sign});
                }
                else{
                    if(plus[nv]!=-INF && plus[nv]!=nnum){
                        cout<<0<<endl;
                        return 0;
                    }
                    plus[nv]=nnum;
                    if(minus[nv]!=INF){
                        ll x = minus[nv]-plus[nv];
                        if(x%2==0){
                            chmax(mi,x/2);
                            chmin(ma,x/2);
                        }
                        else{
                            cout<<0<<endl;
                            return 0;
                        }
                    }
                }
            }
            if(sign==-1){
                if(check[nv]==0){
                    minus[nv]=nnum;
                    chmin(ma,nnum-1);
                    check[nv]=1;
                    q.push({nv,nnum,sign});
                }
                else{
                    if(minus[nv]!=INF && minus[nv]!=nnum){
                        cout<<0<<endl;
                        return 0;
                    }
                    minus[nv]=nnum;
                    if(plus[nv]!=-INF){
                        ll x = minus[nv]-plus[nv];
                        if(x%2==0){
                            chmax(mi,x/2);
                            chmin(ma,x/2);
                        }
                        else{
                            cout<<0<<endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    cout<<max(0LL,ma-mi+1)<<endl;
    return 0;
}