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

ll product(pll a, pll b){
    return(a.first*b.second-a.second*b.first);
}

int main() {
    ll n;cin>>n;
    vector<ll> x(2*n),y(2*n);
    set<pll> st;
    pll xmax = {-INF,-1};
    pll xmin = {INF,-1};
    vector<tuple<ll,ll,ll>> uppos,downpos;
    vector<pll>ups,downs;
    rep(i,0,n){
        cin>>x[i]>>y[i];
        x[n+i]=x[i];y[n+i]=y[i];
        st.insert({x[i],y[i]});
        if(xmax.first<x[i]) xmax={x[i],i};
        if(xmin.first>x[i]) xmin={x[i],i};
    }
    if(xmin.second<xmax.second){
        rep(i,xmin.second,xmax.second+1){
            downs.push_back({x[i],y[i]});
            downpos.push_back({x[i],y[i],-1});
        }
        rep(i,xmax.second,xmin.second+n+1){
            ups.push_back({x[i],y[i]});
            uppos.push_back({x[i],y[i],-1});
        }
    }
    else{
        rep(i,xmax.second,xmin.second+1){
            ups.push_back({x[i],y[i]});
            uppos.push_back({x[i],y[i],-1});
        }
        rep(i,xmin.second,xmax.second+n+1){
            downs.push_back({x[i],y[i]});
            downpos.push_back({x[i],y[i],-1});
        }
    }
    ll q;cin>>q;
    vector<ll> ans(q,0);
    rep(i,0,q){
        ll a,b;cin>>a>>b;
        if(st.count({a,b})){
            ans[i]=-INF;
            continue;
        }
        uppos.push_back({a,b,i});
        downpos.push_back({a,b,i});
    }
    sort(uppos.begin(),uppos.end());
    sort(downpos.begin(),downpos.end());
    reverse(ups.begin(),ups.end());
    ll now = 0,idx = 0;
    while(get<2>(uppos[idx])!=-1)idx++;
    while(now<ups.size()-1){
        pll nowvec = {ups[now+1].first-ups[now].first,ups[now+1].second-ups[now].second};
        idx++;
        while(get<2>(uppos[idx])!=-1){
            ll x_,y_,posid; tie(x_,y_,posid)=uppos[idx];
            ll prod = product(nowvec,make_pair(x_-ups[now].first,y_-ups[now].second));
            if(prod==0) ans[posid]=-INF;
            if(prod<0) ans[posid]++;
            idx++;
        }
        now++;
    }
    now = 0;idx = 0;
    while(get<2>(downpos[idx])!=-1)idx++;
    while(now<downs.size()-1){
        pll nowvec = {downs[now+1].first-downs[now].first,downs[now+1].second-downs[now].second};
        idx++;
        while(get<2>(downpos[idx])!=-1){
            ll x_,y_,posid; tie(x_,y_,posid)=downpos[idx];
            ll prod = product(nowvec,make_pair(x_-downs[now].first,y_-downs[now].second));
            if(prod==0) ans[posid]=-INF;
            if(prod>0) ans[posid]++;
            idx++;
        }
        now++;
    }
    
    rep(i,0,q){
        if(ans[i]==2) cout<<"IN"<<endl;
        else if(ans[i]<0) cout<<"ON"<<endl;
        else cout<<"OUT"<<endl;
    }
    return 0;
}