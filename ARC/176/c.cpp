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
    vector<ll> maxnum(n,INF);
    vector<vector<pll>> edge(n);
    vector<ll> add(n);
    ll num = 0;
    rep(i,0,m){
        ll a,b,c;cin>>a>>b>>c;
        a--;b--;c--;
        edge[c].push_back({a,b});
        chmin(maxnum[a],c);
        chmin(maxnum[b],c);
    }
    rep(i,0,n){
        if(maxnum[i]==INF)num++;
        else add[maxnum[i]]++;
    }
    mint ans = 1;
    rrep(i,n-1,0){
        if(edge[i].size()==0) ans*=num;
        if(edge[i].size()==1){
            auto[a,b]=edge[i][0];
            if(maxnum[a]==maxnum[b] && maxnum[b]==i) ans*=2;
            else if(maxnum[a]==i || maxnum[b]==i){}
            else {
                // cout<<"a"<<endl;
                ans = 0;
                break;
            }
        }
        if(edge[i].size()>=2){
            ll x;
            if(edge[i][0].first == edge[i][1].first ||edge[i][0].first == edge[i][1].second)x = edge[i][0].first;
            else x = edge[i][0].second;
            for(auto p:edge[i])if(x!=p.first && x!=p.second){
                // cout<<"b"<<endl;
                ans =0;
                break;
            }
        }
        //cout<<i<<" "<<num<<" "<<ans.val()<<endl;
        num--;
        num+=add[i];
    }
    cout<<ans.val()<<endl;
    return 0;
}