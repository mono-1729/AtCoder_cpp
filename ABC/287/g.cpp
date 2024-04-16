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

using S = struct 
{
    ll cnt;
    ll sum;
};
ll border;

S op(S x1, S x2) {
    return {x1.cnt+x2.cnt,x1.sum+x2.sum};
} 
bool f(S x){
    return  x.cnt<border;
}
S e() {return {0,0};}

int main() {
    ll n;cin>>n;
    vector<ll> a(n),b(n);
    rep(i,0,n) cin>>a[i]>>b[i];
    set<ll> st;
    rep(i,0,n)st.insert(a[i]);
    ll q;cin>>q;
    vector<tuple<ll,ll,ll>> query(q);
    rep(i,0,q){
        ll type,x,y=-1;cin>>type;
        if(type==3)cin>>x;
        else{
            cin>>x>>y;
            x--;
        }
        if(type==1) st.insert(y);
        query[i]={type,x,y};
    }
    unordered_map<ll,ll> mp;
    ll mpcnt = 0;
    auto itr = st.begin();
    while(itr!=st.end()){
        mp[*itr]=mpcnt;
        itr++;
        mpcnt++;
    }
    vector<ll> nums(st.begin(),st.end());
    segtree<S,op,e>seg(mpcnt);
    rep(i,0,n){
        ll cnt = seg.get(mp[a[i]]).cnt+b[i];
        seg.set(mp[a[i]],{cnt,cnt*a[i]});
    }
    seg.all_prod();
    rep(i,0,q){
        ll type,x,y;
        tie(type,x,y)=query[i];
        if(type==1){
            ll cnt = seg.get(mp[a[x]]).cnt-b[x];
            seg.set(mp[a[x]],{cnt,cnt*a[x]});
            cnt = seg.get(mp[y]).cnt+b[x];
            seg.set(mp[y],{cnt,cnt*y});
            a[x]=y;
        }
        if(type==2){
            ll cnt = seg.get(mp[a[x]]).cnt+y-b[x];
            seg.set(mp[a[x]],{cnt,cnt*a[x]});
            b[x]=y;
        }
        if(type==3){
            border = x;
            if(seg.all_prod().cnt<x){
                cout<<-1<<endl;
                continue;
            }
            ll l = seg.min_left<f>(mpcnt);
            ll ans = 0;
            S tmp = seg.prod(l,mpcnt);
            ans=tmp.sum+(x-tmp.cnt)*nums[l-1];
            cout<<ans<<endl;
        }
    }
    return 0;
}