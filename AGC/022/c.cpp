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
    vector<ll> a(n),b(n);
    rep(i,0,n)cin>>a[i];
    rep(i,0,n)cin>>b[i];
    rep(i,0,n){
        if(a[i]!=b[i] && a[i]<=b[i]*2){
            cout<<-1<<endl;
            return 0;
        }
    }
    unordered_set<ll> st;
    for(ll now=49;now>=0;now--){
        vector<vector<ll>> g(51);
        rrep(x,50,1)if(x<=now || st.count(x)){
            rep(i,1,51)g[i].push_back(i%x);
        }
        bool flg = true;
        rep(i,0,n){
            vector<ll> dist(51,-1);
            queue<ll> q;
            dist[a[i]] = 0;
            q.push(a[i]);
            while(!q.empty()){
                ll v = q.front();q.pop();
                for(auto nv:g[v]){
                    if(dist[nv]==-1){
                        dist[nv]=dist[v]+1;
                        q.push(nv);
                    }
                }
            }
            if(dist[b[i]]==-1){
                flg=false;
                break;
            }
        }
        if(!flg) st.insert(now+1);
    }
    ll ans = 0;
    for(auto x:st)ans+=(1LL<<x);
    cout<<ans<<endl;
    return 0;
}