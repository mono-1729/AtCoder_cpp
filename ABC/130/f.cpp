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

vector<double> times = {0};

struct D{
    vector<double> l,r;
    D():l(3,IINF),r(3,-IINF){}
    void add(double x,int v){
        ++v;
        chmin(l[v],x);
        chmax(r[v],x);
    }
    double get(double t){
        double nl = IINF, nr = -IINF;
        rep(i,0,3){
            chmin(nl,l[i]+i*t);
            chmax(nr,r[i]+i*t);
        }
        return nr-nl;
    }
    void events(){
        rep(i,0,3)rep(j,0,i){
            {
                double x = (l[j]-l[i])/(i-j);
                if(x>0)times.push_back(x);
            }
            {
                double x = (r[j]-r[i])/(i-j);
                if(x>0)times.push_back(x);
            }
        }
    }
};

int main() {
    cout<<fixed<<setprecision(15);
    ll n;cin>>n;
    D xd,yd;
    rep(i,0,n){
        ll x,y;char d;cin>>x>>y>>d;
        if(d=='L')xd.add(x,-1),yd.add(y,0);
        if(d=='R')xd.add(x,1),yd.add(y,0);
        if(d=='U')xd.add(x,0),yd.add(y,1);
        if(d=='D')xd.add(x,0),yd.add(y,-1);
    } 
    xd.events();
    yd.events();
    double ans = INF;
    for(auto time:times){
        chmin(ans,xd.get(time)*yd.get(time));
    }
    cout<<ans<<endl;
    return 0;
}