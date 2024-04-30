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
    vector<unordered_set<ll>> pre(n+1);
    priority_queue<pll> pq;
    vector<pll> ans;
    unordered_map<ll,ll> mp;
    rep(i,1,n+1) pq.push({m,i});
    rep(i,0,m){
        ll a,b;cin>>a>>b;
        pre[a].insert(b);
        ans.push_back({a,b});
    }
    rep(i,1,n+1){
        if(pre[i].size()==0)continue;
        for(auto x:pre[i])mp[x]++;
        vector<pll>tmp;
        unordered_set<ll>check;
        rep(j,0,m-pre[i].size()){
            pll p;
            while(true){
                p = pq.top();pq.pop();
                // cout<<i<<" "<<j<<" "<<p.first<<" "<<p.second<<endl;
                if(mp[p.second]!=0){
                    if(p.first-mp[p.second]>0)pq.push({p.first-mp[p.second],p.second});
                    mp[p.second]=0;
                }
                else if(pre[i].find(p.second)==pre[i].end() &&check.find(p.second)==check.end())break;
                else{
                    tmp.push_back(p);
                }
            }
            ans.push_back({i,p.second});
            check.insert(p.second);
            if(p.first>1) pq.push({p.first-1,p.second});
        }
        for(auto x:tmp)pq.push(x);
    }
    rep(i,1,n+1){
        if(pre[i].size()!=0)continue;
        vector<pll>tmp;
        unordered_set<ll>check;
        rep(j,0,m-pre[i].size()){
            pll p;
            while(true){
                p = pq.top();pq.pop();
                // cout<<i<<" "<<j<<" "<<p.first<<" "<<p.second<<endl;
                if(mp[p.second]!=0){
                    if(p.first-mp[p.second]>0)pq.push({p.first-mp[p.second],p.second});
                    mp[p.second]=0;
                }
                else if(pre[i].find(p.second)==pre[i].end()&&check.find(p.second)==check.end())break;
                else{
                    tmp.push_back(p);
                }
            }
            ans.push_back({i,p.second});
            check.insert(p.second);
            if(p.first>1) pq.push({p.first-1,p.second});
        }
        for(auto x:tmp)pq.push(x);
    }
    cout<<ans.size()<<endl;
    for(auto [a,b]:ans){
        cout<<a<<" "<<b<<endl;
    }
    return 0;
}