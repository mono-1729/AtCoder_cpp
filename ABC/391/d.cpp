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
    ll n, w; cin >> n >> w;
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<tuple<ll, ll, ll>>> event;
    rep(i,0,n){
        ll x, y; cin >> x >> y;
        event.push(make_tuple(y, i, x-1));
    }
    ll q; cin >> q;
    rep(i,0,q){
        ll t, a; cin >> t >> a;
        event.push(make_tuple(t+1, a-1, -i-1));
    }
    vector<ll> ans(q);
    vector<ll> deleted(n, 0);
    vector<ll> setted(w, -1);
    vector<queue<ll>> wait(w); 
    ll cnt = 0;
    unordered_map<ll,ll> mp;
    while(!event.empty()){
        auto [y, i, x] = event.top(); event.pop();
        if(mp[y] == 0){
            mp[y] = 1;
            if(cnt == w){
                event.push(make_tuple(y+1, -INF,-INF));
                cnt = 0;
                rep(j,0,w){
                    deleted[setted[j]] = 1;
                    if(!wait[j].empty()){
                        setted[j] = wait[j].front();
                        wait[j].pop();
                        cnt++;
                    }else{
                        setted[j] = -1;
                    }
                }
            } 
        }
        if(i == -INF) continue;
        if(x >= 0){
            if(setted[x] != -1){
                wait[x].push(i);
            }else{
                setted[x] = i;
                cnt++;
            }
        }else{
            if(deleted[i]){
                ans[-x-1] = 0;
            }else{
                ans[-x-1] = 1;
            }
        }
    }
    rep(i,0,q){
        if(ans[i]) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}