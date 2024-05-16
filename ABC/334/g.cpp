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
    ll h,w;cin>>h>>w;
    mint ans = 0;
    ll sum = 0;
    ll connect_num=0;
    vector<string> s(h);
    rep(i,0,h)cin>>s[i];
    vector<vector<ll>>ord(h,vector<ll>(w)),low(h,vector<ll>(w));
    vector<vector<ll>> check(h,vector<ll>(w,0));
    vector<ll> dx = {1,-1,0,0},dy = {0,0,1,-1};
    auto solve=[&](auto solve, pll v,pll p)->void{
        ll vx=v.first,vy=v.second;
        ll px=p.first,py=p.second;
        ord[vx][vy]=sum++;
        low[vx][vy]=ord[vx][vy];
        check[vx][vy]=1;
        if(px==-1)ans--;
        rep(i,0,4){
            ll nx=vx+dx[i],ny=vy+dy[i];
            if(nx<0 || nx>=h || ny<0 || ny>=w || s[nx][ny]=='.')continue;
            if(check[nx][ny]){
                if(nx!=px || ny!=py)chmin(low[vx][vy],ord[nx][ny]);
            }
            else{
                solve(solve,{nx,ny},v);
                if(nx!=px || ny!=py)chmin(low[vx][vy],low[nx][ny]);
                if(ord[vx][vy]<=low[nx][ny]) ans++;
            }
        }
    };
    rep(i,0,h)rep(j,0,w){
        if(s[i][j]=='#' && check[i][j]==0){
            solve(solve,{i,j},{-1,-1});
            connect_num++;
        }
    }
    // cout<<ans.val()<<" "<<connect_num<<endl;
    ans*=powMod(sum,MOD-2);
    ans+=connect_num;
    cout<<ans.val()<<endl;
    return 0;
}