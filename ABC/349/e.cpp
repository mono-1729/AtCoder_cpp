#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
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
    vector<vector<ll>> a(3, vector<ll>(3));
    rep(i,0,3){
        rep(j,0,3){
            cin>>a[i][j];
        }
    }
    auto solve = [&](auto& solve ,vector<vector<ll>> col,ll tp,ll ap,ll turn)->ll{
        rep(i,0,3){
            if(col[i][0]==col[i][1] &&  col[i][1]==col[i][2] && col[i][0]!=0){
                return col[i][0];
            }
            if(col[0][i]==col[1][i] &&  col[1][i]==col[2][i] && col[0][i]!=0){
                return col[0][i];
            }
        }
        if(col[0][0]==col[1][1] && col[1][1]==col[2][2] && col[0][0]!=0) return col[0][0];
        if(col[0][2]==col[1][1] && col[1][1]==col[2][0] && col[0][2]!=0) return col[0][2];
        if(turn==9){
            if(tp>ap)return 1;
            else if(tp<ap)return 2;
        }
        rep(i,0,3)rep(j,0,3){
            if(col[i][j]!=0)continue;
            vector<vector<ll>> tmp = col;
            tmp[i][j] = (turn%2==0)?1:2;
            if(turn%2==0){
                ll res = solve(solve,tmp,tp+a[i][j],ap,turn+1);
                if(res==1)return 1;
            }else{
                ll res = solve(solve,tmp,tp,ap+a[i][j],turn+1);
                if(res==2)return 2;
            }
        }
        if(turn%2==0) return 2;
        else return 1;
    };
    vector<vector<ll>> x(3,vector<ll>(3,0));
    ll ans = solve(solve,x,0,0,0);
    if(ans==1)cout<<"Takahashi"<<endl;
    else if(ans==2)cout<<"Aoki"<<endl;
    return 0;
}