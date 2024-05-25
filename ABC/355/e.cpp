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

using mint = modint;

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
    ll n,l,r;cin>>n>>l>>r;
    r++;
    vector<vector<ll>> g((1LL<<n)+1);
    vector<ll> par((1LL<<n)+1,-1),dist((1LL<<n)+1,-1);
    for(ll i = 1; i <= 1LL<<n; i*=2){
        for(ll j = 0; j+i <= (1LL<<n); j+=i){
            g[j].push_back(j+i);
            g[j+i].push_back(j);
        }
    }
    queue<ll> q;
    q.push(l);
    dist[l] = 0;
    while(!q.empty()){
        ll v = q.front();q.pop();
        for(auto nv : g[v]){
            if(dist[nv] == -1){
                dist[nv] = dist[v]+1;
                par[nv] = v;
                q.push(nv);
            }
        }
    }
    mint::set_mod(100);
    mint ans = 0;
    while(par[r] != -1){
        //cout<<r<<" "<<par[r]<<endl;
        if(par[r] < r){
            ll cnt = 0;
            ll num = r-par[r];
            while(num > 1){
                num /= 2;
                cnt++;
            }
            cout<<"? "<<cnt<<" "<<par[r]/((ll)pow(2,cnt))<<endl;
            ll x;cin>>x;
            ans+=x;
        }
        else{
            ll cnt = 0;
            ll num = -r+par[r];
            while(num > 1){
                num /= 2;
                cnt++;
            }
            cout<<"? "<<cnt<<" "<<r/((ll)pow(2,cnt))<<endl;
            ll x;cin>>x;
            ans-=x;
        }
        r=par[r];
    }
    cout<<"! "<<ans.val()<<endl;

    return 0;
}